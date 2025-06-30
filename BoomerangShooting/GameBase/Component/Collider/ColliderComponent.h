#pragma once
#include "GameBase/Component.h"
#include "GameBase/Component/Transform/Transform.h"
#include "GameBase/Actor.h"

class CommonResources;

//判定時のタイプ
enum class CollisionType
{

	FIXED     = 1 ,	   //固定
	COLLISION = 2,	   //移動
	TRIGGER   = 3      //すり抜け

};


class ColliderComponent : public Component
{
public:

	//当たり判定の種類
	enum  class ColliderTag
	{
		AABB = 1 << 0
		, OBB = 1 << 1
		, SPHERE = 1 << 2
	};

public:	
	//当たり判定の種類の取得
	const ColliderTag GetCollisionTag() { return m_collisionTag; }
	//判定時の種類の取得
	CollisionType GetCollisionType() const { return m_collisionType; }

	//当たったコライダーの取得
	const std::vector<ColliderComponent*> GetHitObject() { return m_hitCollider; };
	//当たったコライダーの登録
	void SetHitObject(ColliderComponent* ColliderComponent) { m_hitCollider.push_back(ColliderComponent); };
	//押し出し
	void SetPushBack(DirectX::SimpleMath::Vector3 puchBackVector);
	//補正座標の取得
	const DirectX::SimpleMath::Vector3& OffsetPosition() { return m_offsetPosition; }
	//補正座標のセット
	void SetOffsetPosition(DirectX::SimpleMath::Vector3 offset) {m_offsetPosition = offset; }
	//当たり判定を行わないオブジェクトタグのセット
	void SetNotHitObjectTag(std::vector<Actor::ObjectTag> tags) { m_notHitTag = tags; }
	//当たり判定を行わないオブジェクトタグの取得
	std::vector<Actor::ObjectTag> GetNotHitObjectTag() { return m_notHitTag; }

public:
	//コンストラクタ
	ColliderComponent(Actor* owner,ColliderTag tag , CollisionType type);

	//デストラクタ
	virtual ~ColliderComponent() override;

	// 更新処理
	void Update(const float& deltaTime) override;
	//派生用の更新処理
	virtual void UpdateCollider() {};
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
	, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
	, DirectX::BasicEffect* effect
	, ID3D11InputLayout* inputlayout);
	//派生用の描画処理
	virtual void RenderCollider(const DirectX::SimpleMath::Matrix& view,const DirectX::SimpleMath::Matrix& projection
		, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
		, DirectX::BasicEffect* effect
		, ID3D11InputLayout* inputlayout) {
		UNREFERENCED_PARAMETER(view);
		UNREFERENCED_PARAMETER(projection);
		UNREFERENCED_PARAMETER(batch);
		UNREFERENCED_PARAMETER(effect);
		UNREFERENCED_PARAMETER(inputlayout);
	};


	//当たったコライダーの削除
	bool DleteHitObject(ColliderComponent* object);

private:

	//当たり判定の種類
	ColliderTag m_collisionTag;
	//判定時の種類
	CollisionType m_collisionType;
	//当たったオブジェクトの格納変数
	std::vector<ColliderComponent*> m_hitCollider;
	//補正座標
	DirectX::SimpleMath::Vector3 m_offsetPosition;
	//当たり判定を行わないTag
	std::vector<Actor::ObjectTag> m_notHitTag;

};


class AABB : public ColliderComponent
{
public:
	//バウンディングボックスの取得
	DirectX::BoundingBox* GetBoundingBox();
	//バウンディングスフィアの取得
	DirectX::BoundingSphere* GetBoundingSphere();

	//初期Extentsの取得
	DirectX::SimpleMath::Vector3 GetInitialExtents() { return m_initialExtents; }
	//初期半径の取得
	float GetInitialRaduis() { return m_initialRadius; }

public:
	//コンストラクタ
	AABB(Actor* owner, ColliderTag tag, CollisionType type
	,const DirectX::SimpleMath::Vector3& extents
	, const float& radius);
	//デストラクタ
	~AABB() override;

	//派生用の更新処理
	void UpdateCollider() override ;
	//派生用の描画処理
	void RenderCollider(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
		, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
		, DirectX::BasicEffect* effect
		, ID3D11InputLayout* inputlayout) override;

	//ボックスの更新
	void BoxUpdate();
	//スフィアの更新
	void SphereUpdate();

private:
	//バウンディングボックス
	std::unique_ptr<DirectX::BoundingBox> m_boundingBox;
	//バウンディングスフィア
	std::unique_ptr<DirectX::BoundingSphere> m_boundingSphere;

	//初期Extents
	DirectX::SimpleMath::Vector3 m_initialExtents;
	//初期半径
	float m_initialRadius;

};


class OBB : public ColliderComponent
{
public:
	//バウンディングボックスの取得
	DirectX::BoundingOrientedBox* GetBoundingOrientedBox();
	//バウンディングスフィアの取得
	DirectX::BoundingSphere* GetBoundingSphere();

	//初期Extentsの取得
	DirectX::SimpleMath::Vector3 GetInitialExtents() { return m_initialExtents; }
	//初期半径の取得
	float GetInitialRaduis() { return m_initialRadius; }

public:
	//コンストラクタ
	OBB(Actor* owner, ColliderTag tag, CollisionType type
		, const DirectX::SimpleMath::Vector3& extents
		,DirectX::SimpleMath::Quaternion rotation
		, const float& radius);
	//デストラクタ
	~OBB() override;

	//派生用の更新処理
	void UpdateCollider() override;
	//派生用の描画処理
	void RenderCollider(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
		, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
		, DirectX::BasicEffect* effect
		, ID3D11InputLayout* inputlayout) override;

	//ボックスの更新
	void BoxUpdate();
	//スフィアの更新
	void SphereUpdate();


private:
	//バウンディングボックス
	std::unique_ptr<DirectX::BoundingOrientedBox> m_boundingOrientedBox;
	//バウンディングスフィア
	std::unique_ptr<DirectX::BoundingSphere> m_boundingSphere;

	//初期Extents
	DirectX::SimpleMath::Vector3 m_initialExtents;
	//初期半径
	float m_initialRadius;

};
