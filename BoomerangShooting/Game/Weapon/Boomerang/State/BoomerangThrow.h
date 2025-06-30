#pragma once
#include "GameBase/Interface/IState.h"

class BoomerangStateMachine;
class Boomerang;
class Player;

class BoomerangThrow : public IState
{
private:
	//状態
	enum  class State
	{
		SPINECURVE      //投げる
		, CHASE_TO_PLAYER   //返ってくる
	};


	static constexpr float TARGET_LENGTH{ 5.0f };



public:
	//コンストラクタ
	BoomerangThrow(BoomerangStateMachine* stateMahine, Boomerang* boomerang,Player* player);
	//デストラクタ
	~BoomerangThrow() override;

	// 更新する
	void Update(const float& deltaTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

private:
	//スプライン曲線の基準点の作成
	void CreateSplineCurvePositon();

	//スプライン曲線
	void SplineCurve(const float& deltaTime);
	//プレイヤを追いかける
	void ChaseToPlayer(const float& deltaTime);


	//回転
	void Rotation(const float& deltaTime);
	//回転情報の切り替え
	void ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec);


private:
	//ブーメラン
	Boomerang* m_boomerang;
	//ステートマシーン
	BoomerangStateMachine* m_stateMahine;
	//
	Player* m_player;

	//スプライン曲線の座標
	std::vector<DirectX::SimpleMath::Vector3> m_splineCurvePosition;
	//添え字
	int m_index;
	//経過時間
	float m_totalTime;
	//状態
	State m_state;
	//回転の情報
	std::pair<DirectX::SimpleMath::Quaternion, DirectX::SimpleMath::Quaternion> m_rotationDatas;
	//横回転
	DirectX::SimpleMath::Quaternion m_horizontalRotation;
	//初期回転
	DirectX::SimpleMath::Quaternion m_initialRotation;
	//動く方向
	DirectX::SimpleMath::Vector3 m_moveDirection;
	//投げる軌道の基準座標
	std::vector<DirectX::SimpleMath::Vector3> m_throwbasePosition;


};

