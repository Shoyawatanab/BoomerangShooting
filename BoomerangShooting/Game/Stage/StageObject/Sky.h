#pragma once
/*
	@file	Sky.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"

// 前方宣言
class CommonResources;




class Sky 
{
public:


public:
	//コンストラク
	Sky(CommonResources* resources
		, DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//デストラクタ
	~Sky() ;

	//IObject
		//初期化
	void Initialize() ;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	//更新処理
	void  Update(const float& elapsedTime) ;

private:

	// モデル
	DirectX::Model* m_model;
};
