#include "pch.h"
#include "Animation.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">所有者</param>
Animation::Animation(Actor* owner)
	:
	m_actor{owner}
	,m_isPositionUpdate{false}
	,m_isRotateUpdate{false}
	,m_animationTotalTime{}
	,m_initialPosition{}
	,m_initialRotate{}
	,m_initialScale{}
{

	//所有者の初期状態を取得
	auto transform = m_actor->GetTransform();
	m_initialPosition = transform->GetPosition();
	m_initialRotate = transform->GetRotate();
	m_initialScale = transform->GetScale();

}

/// <summary>
/// デストラクタ
/// </summary>
Animation::~Animation()
{
	m_positoinData.second.clear();
	m_rotateData.second.clear();
}

 
/// <summary>
/// 更新処理
/// </summary>
/// <param name="animationTime">アニメーションの経過時間</param>
void Animation::Update(const float& animationTime)
{
	//座標の更新を行うか
	if (m_isPositionUpdate)
	{
		//座標
		PositionUpdate(animationTime);

	}
	//回転の更新を行うか
	if (m_isRotateUpdate)
	{
		//回転
		RotationUpdate(animationTime);

	}

}

/// <summary>
/// 座標データの追加
/// </summary>
/// <param name="framTime">フレーム時間</param>
/// <param name="position">座標</param>
void Animation::AddPositionData(float framTime, DirectX::SimpleMath::Vector3 position)
{
	using namespace DirectX::SimpleMath;


	//フレームの追加
	KeyFram fram = { framTime,position };
	m_positoinData.second.push_back(fram);

	//更新を行うかを有効に
	m_isPositionUpdate = true;
	
}

/// <summary>
/// 回転データの追加
/// </summary>
/// <param name="framTime">フレーム時間</param>
/// <param name="rotate">回転</param>
void Animation::AddRotateData(float framTime, DirectX::SimpleMath::Vector3 rotate)
{

	//フレームの追加
	KeyFram fram = { framTime,rotate };
	m_rotateData.second.push_back(fram);

	//更新を行うかを有効に
	m_isRotateUpdate = true;

}

/// <summary>
/// リセット
/// </summary>
void Animation::Reset()
{
	m_positoinData.first = 0;
	m_rotateData.first = 0;

	//ローカル回転の更新
	m_actor->GetTransform()->SetPosition(m_initialPosition);
	m_actor->GetTransform()->SetRotate(m_initialRotate);

}

/// <summary>
/// データの並び替え
/// </summary>
void Animation::DataSort()
{

	//座標の並び替え
	PositionSort();
	//回転の並び替え
	RotateSort();


}
/// <summary>
/// 座標の並び替え
/// </summary>
void Animation::PositionSort()
{
	using namespace DirectX::SimpleMath;

	//データがなければ
	if (m_positoinData.second.empty())
	{
		return;
	}
	//１以上なら
	if (m_positoinData.second.size() > 1)
	{
		//回転情報をTimeで昇順に並び替え
		std::sort(m_positoinData.second.begin(), m_positoinData.second.end(),
			[](const KeyFram& a, const KeyFram& b)
			{
				return a.Time < b.Time;
			});
	}


	//はじめが0.0fではい場合
	if (m_positoinData.second[0].Time != 0.0f)
	{
		//初めにゼロ初期化
		m_positoinData.second.insert(m_positoinData.second.begin(), { 0.0f,Vector3::Zero });
	}
	//終わりがアニメーション時間でない場合
	if (m_positoinData.second[m_positoinData.second.size() - 1].Time != m_animationTotalTime)
	{
		//終わりにゼロ初期化
		m_positoinData.second.push_back({ m_animationTotalTime,Vector3::Zero });

	}

}

/// <summary>
/// 回転の並び替え
/// </summary>
void Animation::RotateSort()
{

	using namespace DirectX::SimpleMath;

	//データがなければ
	if (m_rotateData.second.empty())
	{
		return;
	}
	//１以上なら
	if (m_rotateData.second.size() > 1)
	{
		//回転情報をTimeで昇順に並び替え
		std::sort(m_rotateData.second.begin(), m_rotateData.second.end(),
			[](const KeyFram& a, const KeyFram& b)
			{
				return a.Time < b.Time;
			});
	}


	//はじめが0.0fではい場合
	if (m_rotateData.second[0].Time != 0.0f)
	{
		//初めにゼロ初期化
		m_rotateData.second.insert(m_rotateData.second.begin(), { 0.0f,Vector3::Zero });


	}
	//終わりがアニメーション時間でない場合
	if (m_rotateData.second[m_rotateData.second.size() - 1].Time != m_animationTotalTime)
	{
		//終わりにゼロ初期化
		m_rotateData.second.push_back({ m_animationTotalTime,Vector3::Zero });

	}

	

}

/// <summary>
/// 座標の更新
/// </summary>
void Animation::PositionUpdate(const float& animationTime)
{
	using namespace DirectX::SimpleMath;

	//添え字
	int index = m_positoinData.first;

	//初めの時間
	float startTime = m_positoinData.second[index].Time;
	//終わりの時間
	float endTime = m_rotateData.second[index + 1].Time;
	//初めのデータ
	Vector3 startData = m_positoinData.second[index].Data;
	//終わりのデータ
	Vector3 endData = m_positoinData.second[index + 1].Data;



	//割合
	float ratio = 0;
	//０同時では計算をしないため
	if (endTime != startTime)
	{
		ratio = (animationTime - startTime) / (endTime - startTime);
	}
	//割合が1を超えないように
	ratio = std::min(ratio, 1.0f);

	//回転
	Vector3 position = Vector3::SmoothStep(startData, endData, ratio);

	//ローカル座標の更新
	m_actor->GetTransform()->SetPosition(m_initialPosition + position);

	//フレームの切り替え
	if (animationTime >= endTime)
	{
		m_positoinData.first++;
		m_positoinData.first = m_positoinData.first % m_positoinData.second.size();
	}




}

/// <summary>
/// 回転の更新
/// </summary>
void Animation::RotationUpdate(const float& animationTime)
{
	using namespace DirectX::SimpleMath;
	
	//添え字
	int index = m_rotateData.first;

	//初めの時間
	float startTime = m_rotateData.second[index].Time;
	//終わりの時間
	float endTime = m_rotateData.second[index + 1].Time;
	//初めのデータ
	Vector3 startData = m_rotateData.second[index].Data;
	//終わりのデータ
	Vector3 endData = m_rotateData.second[index + 1].Data;


	//データから回転を作成
	Quaternion startRotation = Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(startData.y),
		DirectX::XMConvertToRadians(startData.x),
		DirectX::XMConvertToRadians(startData.z)
	);
	Quaternion endRotation = Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(endData.y),
		DirectX::XMConvertToRadians(endData.x),
		DirectX::XMConvertToRadians(endData.z)
	);

	//割合
	float ratio = 0;
	//０同時では計算をしないため
	if (endTime != startTime)
	{
		ratio = (animationTime - startTime) / (endTime - startTime);
	}

	//割合が1を超えないように
	ratio = std::min(ratio, 1.0f);

	//回転
	Quaternion rotation = Quaternion::Slerp(startRotation, endRotation, ratio);

	//ローカル回転の更新
	m_actor->GetTransform()->SetRotate(m_initialRotate *  rotation);

	//フレームの切り替え
	if (animationTime >= endTime)
	{
		m_rotateData.first++;
		m_rotateData.first =  m_rotateData.first % m_rotateData.second.size();
	}

}

