/*
	1つのパーツに対するアニメーションを行うクラス
*/

#pragma once
#include "GameBase/Actor.h"

class Animation
{
public:
	//キーフレームアニメーション構造体
	struct KeyFram
	{
		float Time;                             //経過時間
		DirectX::SimpleMath::Vector3 Data;	    //経過時間に対してのデータ
	};

public:
	//アニメーション全体の時間のセット
	void SetAnimationTotalTime(const float& time) { m_animationTotalTime = time; };

public:
	//コンストラクタ
	Animation(Actor* owner);
	//デストラクタ
	~Animation();
	//更新処理
	void Update(const float& animationTime);
	//座標キーフレームの追加
	void AddPositionData(float framTime,DirectX::SimpleMath::Vector3 position);
	//回転キーフレームの追加
	void AddRotateData(float framTime,DirectX::SimpleMath::Vector3 rotae);
	//リセット
	void Reset();
	//データの並び替え
	void DataSort();


private:
	//座標の並び替え
	void PositionSort();
	//回転の並び替え
	void RotateSort();

	//座標の更新
	void PositionUpdate(const float& animationTime);
	//回転の更新
	void RotationUpdate(const float& animationTime);


private:
	//所有者
	Actor* m_actor;
	//座標のデータ
	std::pair<int, std::vector<KeyFram>> m_positoinData;
	//回転のデータ
	std::pair<int, std::vector<KeyFram>> m_rotateData;
	//座標の更新をするか
	bool m_isPositionUpdate;
	//回転の更新をするか
	bool m_isRotateUpdate;
	//アニメーション全体の時間
	float m_animationTotalTime;
	//オブジェクトの初期座標
	DirectX::SimpleMath::Vector3 m_initialPosition;
	//オブジェクトの初期回転
	DirectX::SimpleMath::Quaternion m_initialRotate;
	//オブジェクトの初期大きさ
	DirectX::SimpleMath::Vector3 m_initialScale;

};