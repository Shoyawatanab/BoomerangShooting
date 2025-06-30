#include "pch.h"
#include "Animator.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "GameBase/Component/Components.h"
#include "GameBase/Animation/Animation.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="animationName">アニメーション名</param>
/// <param name="actors">アニメーションさせたいオブジェクト</param>
Animator::Animator(Actor* owner
	, const std::string& animationName
	, const std::string& filePath
	, std::vector<std::pair<std::string, Actor*>> actors)
	:
	m_ower{owner}
	,m_animationName{animationName}
	,m_isLoop{false}
	, m_animationTotalTime{}
	,m_partsData{}
	, m_animationTime{}
	,m_isEnd{false}
{

	//Animationの作成
	for (auto& [name, actor] : actors) 
	{
		m_partsData[name] = std::make_unique<Animation>(actor);
	}

	//アニメーションの読み込み　Jsonファイルから
	LoadData(filePath);

	//データの並び替え
	for (auto& parts : m_partsData)
	{
		parts.second->DataSort();
	}

}



/// <summary>
/// デストラクタ
/// </summary>
Animator::~Animator()
{
	m_partsData.clear();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
/// <returns>ture: 実行中　false :終了</returns>
bool Animator::Update(const float& deltaTime)
{

	//パーツごとのアニメーションを更新
	for (auto& parts : m_partsData)
	{
		//アニメーションの更新
		parts.second->Update(m_animationTime);

	}
	
	//時間の加算
	m_animationTime += deltaTime;
	
	//アニメーションが一通り終わったら
	if (m_animationTime >= m_animationTotalTime)
	{ 
		m_isEnd = true;
		//アニメーション終了
		return true;
	}
	
	//アニメーション中
	return false;
}



/// <summary>
/// アニメーションの再生
/// </summary>
void Animator::PlayAnimation()
{
}

/// <summary>
/// 再実行
/// </summary>
void Animator::Rerun()
{
	//経過時間のリセット
	m_animationTime = 0.0f;
	m_isEnd = false;

	for (auto& parts : m_partsData)
	{
		//Animationのリセット
		parts.second->Reset();
	}
}

/// <summary>
/// アニメーション情報の読み込み
/// </summary>

/// <param name="filePath">ファイルパス</param>
void Animator::LoadData(std::string filePath)
{
	using namespace DirectX::SimpleMath;
	using json = nlohmann::json;

	std::ifstream file(filePath);

	//ファイルが開けないとき
	if (!file.is_open())
	{
		throw std::runtime_error("jsonファイルが開けません");
	}

	//ファイルの内容をJSONオブジェックとしてパース
	json data = json::parse(file);


	//アニメーションの種類

	//アニメーションのトータル時間
	m_animationTotalTime = data["AnimationTime"];

	//アニメーションのスピード
	m_speed = data["AnimationSpeed"];

	//ループ再生かどうか
	m_isLoop = data["Loop"];

	//アニメーション時間のセット
	for (auto& parts : m_partsData)
	{
		parts.second->SetAnimationTotalTime(m_animationTotalTime);
	}


	//KeyFrame[](ピンク色)内のデータの{}(青色)の要素だけ回す
	for (const auto& frameData : data["KeyFrame"])
	{

		//フレームの時間の取得
		float frameTime = frameData["FreamTime"];


		//部位ごとの情報の取得
		for (const auto& partsData : frameData["Parts"])
		{
			std::string partsName = partsData["PartName"];

			//パーツデータに同じ名前があるか
			auto it = m_partsData.find(partsName);

			//なければ次へ
			if (it == m_partsData.end())
			{
				continue;
			}


			//Positionがあるか
			if (partsData.contains("Position"))
			{
				 Vector3 position= DirectX::SimpleMath::Vector3(
					partsData["Position"]["x"],           //Positionの要素のxの要素を代入x値
					partsData["Position"]["y"],           //Positionの要素のxの要素を代入y値
					partsData["Position"]["z"]            //Positionの要素のxの要素を代入z値
				);
				//Positionとフレーム時間の代入
				it->second->AddPositionData(frameTime,position);

			}



			//Rotationがあるか
			if (partsData.contains("Rotation"))
			{
				//Positionの要素を代入
				Vector3 rotation = DirectX::SimpleMath::Vector3(
					partsData["Rotation"]["x"],           //Positionの要素のxの要素を代入x値
					partsData["Rotation"]["y"],           //Positionの要素のxの要素を代入y値
					partsData["Rotation"]["z"]            //Positionの要素のxの要素を代入z値
				);
	
				//Rotationとフレーム時間の代入
				it->second->AddRotateData(frameTime, rotation);

			}
						
		}
	}

}






