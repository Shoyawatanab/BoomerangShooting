/*
* ステーとパターンのインターフェース
*/
#pragma once
#include "pch.h"

class CommonResources;

class IEffect
{
public:
	//エフェクトの種類
	enum  class EffectType
	{

		EXPLOSION
		,PLAYER_DAMAGE
		,PARTICLE
		, HIT_EFFECT
		,CHARGE_EFFECT
	};

public:
	//デストラクタ
	virtual ~IEffect() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	//描画
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) = 0;
	//有効かどうかの取得
	virtual const bool& GetIsActive() = 0;
	//有効かどうかの登録
	virtual void SetIsActive(const bool& isActive) = 0;
	//エフェクトの種類の取得
	virtual EffectType GetEffectType() = 0;
	//座標の登録
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	//大きさの登録
	virtual void SetScale(const DirectX::SimpleMath::Vector3& scale) = 0;
	//作成
	virtual void Create(void* datas) = 0;
};
