#pragma once


class ParticleUtility
{
public:
	//	座標の取得
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
	//スケールの取得
	const DirectX::SimpleMath::Vector3& GetNowScale() { return m_nowScale; }
	//色の取得
	const DirectX::SimpleMath::Color& GetNowColor() { return m_nowColor; }

public:
	//	関数
	//	コンストラクタ（初期設定）
	ParticleUtility(
		float life,
		const DirectX::SimpleMath::Vector3& pos,
		const DirectX::SimpleMath::Vector3& velocity,
		const DirectX::SimpleMath::Vector3& accele,
		const DirectX::SimpleMath::Vector3& startScale,
		const DirectX::SimpleMath::Vector3& endScale,
		const DirectX::SimpleMath::Color& startColor
		, const DirectX::SimpleMath::Color& endColor);
	//	デストラクタ
	~ParticleUtility();

	//	更新
	bool Update(const float& elapsedTime);


private:
	//	関数
	//	座標
	DirectX::SimpleMath::Vector3 m_position;

	//	速度
	DirectX::SimpleMath::Vector3 m_velocity;
	//	加速度
	DirectX::SimpleMath::Vector3 m_accele;

	//	スケール
	DirectX::SimpleMath::Vector3 m_nowScale;
	DirectX::SimpleMath::Vector3 m_startScale;
	DirectX::SimpleMath::Vector3 m_endScale;

	//	生存時間
	float m_life;
	float m_startLife;

	//	カラー
	DirectX::SimpleMath::Color m_nowColor;
	DirectX::SimpleMath::Color m_startColor;
	DirectX::SimpleMath::Color m_endColor;

};

