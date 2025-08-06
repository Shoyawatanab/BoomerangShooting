//--------------------------------------------------------------------------------------
// File: ParticleUtil.cpp
//
// パーティクルユーティリティクラス
// positionや速度などパーティクル１つに必要な要素を格納
// 更新時に生存時間や座標、大きさなどを再計算し、
// 寿命が尽きたらfalseを返して削除を促す
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Particleutility.h"
#include "GameBase/Common/Commons.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

using namespace DirectX;

const static float ENDLESS = -100.0f;

/// <summary>
/// コンストラクタ
/// 引数は初期設定用の数値
/// </summary>
/// <param name="life">生存時間</param>
/// <param name="pos">座標</param>
/// <param name="velocity">速度</param>
/// <param name="accele">加速度</param>
/// <param name="startScale">初期サイズ</param>
/// <param name="endScale">最終サイズ</param>
/// <param name="startColor">初期色</param>
/// <param name="endColor">最終色</param>
ParticleUtility::ParticleUtility(
	float life
	, const DirectX::SimpleMath::Vector3& pos
	, const DirectX::SimpleMath::Vector3& velocity
	, const DirectX::SimpleMath::Vector3& accele
	, const DirectX::SimpleMath::Vector3& startScale
	, const DirectX::SimpleMath::Vector3& endScale
	, const DirectX::SimpleMath::Color& startColor
	, const DirectX::SimpleMath::Color& endColor)
	:
	m_position{}
	, m_velocity{}
	, m_accele{}
	, m_nowScale{}
	, m_startScale{}
	, m_endScale{}
	, m_life{}
	, m_startLife{}
	, m_nowColor{}
	, m_startColor{}
	, m_endColor{}
{
	//	与えられた生存時間（s）を取得
	m_startLife =
		m_life = life;

	//	初期位置を取得
	m_position = pos;
	//	移動ベクトルを取得
	m_velocity = velocity;
	//	加速度ベクトルを取得
	m_accele = accele;

	//	初めのサイズを取得
	m_startScale =
		m_nowScale = startScale;
	//	終了のサイズを取得
	m_endScale = endScale;


	//	初めの色を取得
	m_startColor =
		m_nowColor = startColor;
	//	終了の色を取得
	m_endColor = endColor;
}

/// <summary>
/// デストラクタ
/// </summary>
ParticleUtility::~ParticleUtility()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>ture 生存  false　終了 </returns>
bool ParticleUtility::Update(const float& elapsedTime)
{

	//	スケール。現在の生存時間から、大きさをLerpで算出する
	m_nowScale = SimpleMath::Vector3::Lerp(m_startScale, m_endScale, 1.0f - m_life / m_startLife);
	//	色。現在の生存時間から、色をLerpで算出する
	m_nowColor = SimpleMath::Color::Lerp(m_startColor, m_endColor, 1.0f - m_life / m_startLife);
	//	速度の計算。経過時間と加速度を掛け算して足すことで、加速度を考慮して移動速度を変化させていく
	m_velocity += m_accele * elapsedTime;
	//	座標の計算。経過時間と移動速度から、現在の座標を算出する
	m_position += m_velocity * elapsedTime;
	//	ライフを減らしていく
	m_life -= elapsedTime;
	//	ライフが0未満なら自身を消してもらう
	if (m_life < 0.0f)
	{
		return false;
	}

	return true;

}


