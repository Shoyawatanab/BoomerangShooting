#include "pch.h"
#include "ColliderComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/Microsoft/DebugDraw.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="tag">当たり判定の種類</param>
/// <param name="type">判定の種類</param>
ColliderComponent::ColliderComponent(Actor* owner, ColliderTag tag, CollisionType type)
	:
	Component(owner)
	,m_collisionTag{tag}
	,m_collisionType{type}
	, m_offsetPosition{ DirectX::SimpleMath::Vector3::Zero }
{
	//マネージャーの取得
	auto collisitionManager = GetActor()->GetScene()->GetCollisionManager();
	//マネージャーに追加
	collisitionManager->AddCollider(this);
	//マネージャーの取得
	auto renderManager = GetActor()->GetScene()->GetRenderMangaer();
	//マネージャーに追加
	renderManager->AddCollider(this);

}


/// <summary>
/// デストラクタ
/// </summary>
ColliderComponent::~ColliderComponent()
{
	//削除
	auto collisionManager = GetActor()->GetScene()->GetCollisionManager();
	collisionManager->RemoveCollider(this);


}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void ColliderComponent::Update(const float& deltaTime)
{

	//派生先更新処理
	UpdateCollider();

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
/// <param name="batch">プリミティブバッチ</param>
/// <param name="effect">ベーシックエフェクト</param>
/// <param name="inputlayout">インプットレイアウト</param>
void ColliderComponent::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
	,DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch, DirectX::BasicEffect* effect, ID3D11InputLayout* inputlayout)
{
	//派生先の描画処理
	RenderCollider(view, projection, batch, effect, inputlayout);
}

/// <summary>
/// 当たったコライダーの削除
/// </summary>
/// <param name="object">コンポーネント</param>
/// <returns>true：削除できた　false：できなかった</returns>
bool ColliderComponent::DleteHitObject(ColliderComponent* object)
{
	size_t initialSize = m_hitCollider.size();
	//オブジェクトがあれば削除
	m_hitCollider.erase(std::remove(m_hitCollider.begin(), m_hitCollider.end(), object), m_hitCollider.end());
	//削除できたかどうか
	if (m_hitCollider.size() < initialSize)
	{
		//削除できたら
		return true;
	}
	return false;
};



/// <summary>
/// 押し出し処理
/// </summary>
/// <param name="pushBack">押し出しベクトル</param>
void ColliderComponent::SetPushBack(DirectX::SimpleMath::Vector3 pushBackVector)
{
	//オブジェクトの押し出し
	GetActor()->GetTransform()->Translate(pushBackVector);
	//派生先のバウンディングの更新
	UpdateCollider();

}





/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="tag">当たり判定の種類</param>
/// <param name="type">判定の種類</param>
/// <param name="position">中心座標</param>
/// <param name="extents">バウンディングボックスの大きさ</param>
/// <param name="radius">バウンディングスフィアの大きさ</param>
AABB::AABB(Actor* owner, ColliderTag tag, CollisionType type
	, const DirectX::SimpleMath::Vector3& extents
	, const float& radius)
	:
	ColliderComponent(owner,tag,type)
	,m_initialExtents{extents}
	,m_initialRadius{radius}
{
	
	using namespace DirectX;

	//バウンディングボックスるの作成
	m_boundingBox = std::make_unique<BoundingBox>();
	//大きさの設定
	m_boundingBox->Extents = extents;

	//バウンディングスフィアの作成
	m_boundingSphere = std::make_unique<BoundingSphere>();
	//大きさの設定
	m_boundingSphere->Radius = radius;


}

/// <summary>
/// デストラクタ
/// </summary>
AABB::~AABB()
{
}

/// <summary>
/// 個別更新処理
/// </summary>
void AABB::UpdateCollider()
{

	BoxUpdate();
	
	SphereUpdate();

}



/// <summary>
/// 当たり判定の描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
/// <param name="batch">プリミティブバッチ</param>
/// <param name="effect">ベーシックエフェクト</param>
/// <param name="inputlayout">インプットレイアウト</param>
void AABB::RenderCollider(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
	,DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch, DirectX::BasicEffect* effect, ID3D11InputLayout* inputlayout)
{

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	effect->SetView(view);
	effect->SetProjection(projection);
	effect->Apply(context);

	auto states = CommonResources::GetInstance()->GetCommonStates();
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);	// 透過しない
	context->OMSetDepthStencilState(states->DepthDefault(), 0);			// Ｚバッファを使用する
	context->RSSetState(states->CullNone());							// ポリゴンの両面を描画する
	context->IASetInputLayout(inputlayout);							// 入力レイアウトを設定する

	DirectX::XMVECTOR color = DirectX::Colors::Yellow;


#ifdef _DEBUG
	// プリミティブ描画を開始する
	batch->Begin();

	// 境界スフィアを描画する
	DX::Draw(batch, *m_boundingSphere, color);
	DX::Draw(batch, *m_boundingBox, color);
	// プリミティブ描画を終了する
	batch->End();

#endif

}

/// <summary>
/// ボックスの更新
/// </summary>
void AABB::BoxUpdate()
{
	auto scale = GetActor()->GetTransform()->GetWorldScale();
	//大きさの更新
	m_boundingBox->Extents = GetInitialExtents() * scale;
	//座標の更新
	m_boundingBox->Center = GetActor()->GetTransform()->GetRotatePosition() + OffsetPosition();

}

/// <summary>
/// スフィアの更新
/// </summary>
void AABB::SphereUpdate()
{
	//座標の更新
	m_boundingSphere->Center = GetActor()->GetTransform()->GetRotatePosition() + OffsetPosition();
	auto scale = GetActor()->GetTransform()->GetWorldScale();
	//大きさの更新
	m_boundingSphere->Radius = GetInitialRaduis() * std::max({ scale.x,scale.y,scale.z });

}

/// <summary>
/// バウンディングボックスの取得
/// </summary>
/// <returns></returns>
DirectX::BoundingBox* AABB::GetBoundingBox()
{
	BoxUpdate();

	return m_boundingBox.get();
}


/// <summary>
/// バウンディングスフィアの取得
/// </summary>
/// <returns></returns>
DirectX::BoundingSphere* AABB::GetBoundingSphere()
{
	
	SphereUpdate();

	return m_boundingSphere.get();
}



/// <summary>
/// コンストラク
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="tag">当たり判定の種類</param>
/// <param name="type">判定の種類</param>
/// <param name="position">中心座標</param>
/// <param name="extents">バウンディングボックスの大きさ</param>
/// <param name="rotation">バウンディングボックスの回転</param>
/// <param name="radius">バウンディングスフィアの大きさ</param>
OBB::OBB(Actor* owner, ColliderTag tag, CollisionType type
	, const DirectX::SimpleMath::Vector3& extents
	, DirectX::SimpleMath::Quaternion rotation
	, const float& radius)
	:
	ColliderComponent(owner,tag,type)
	, m_initialExtents{ extents }
	, m_initialRadius{ radius }
{

	using namespace DirectX;

	//バウンディングボックスるの作成
	m_boundingOrientedBox = std::make_unique<BoundingOrientedBox>();
	//大きさの設定
	m_boundingOrientedBox->Extents = extents;
	//回転の設定
	m_boundingOrientedBox->Orientation = rotation;

	//バウンディングスフィアの作成
	m_boundingSphere = std::make_unique<BoundingSphere>();
	//大きさの設定
	m_boundingSphere->Radius = radius;


}

/// <summary>
/// デストラクタ
/// </summary>
OBB::~OBB()
{
}

/// <summary>
/// コライダーの更新
/// </summary>
void OBB::UpdateCollider()
{

	BoxUpdate();

	SphereUpdate();

}

/// <summary>
/// 当たり判定の描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
/// <param name="batch">プリミティブバッチ</param>
/// <param name="effect">ベーシックエフェクト</param>
/// <param name="inputlayout">インプットレイアウト</param>
void OBB::RenderCollider(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch, DirectX::BasicEffect* effect, ID3D11InputLayout* inputlayout)
{

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	effect->SetView(view);
	effect->SetProjection(projection);
	effect->Apply(context);

	auto states = CommonResources::GetInstance()->GetCommonStates();
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);	// 透過しない
	context->OMSetDepthStencilState(states->DepthDefault(), 0);			// Ｚバッファを使用する
	context->RSSetState(states->CullNone());							// ポリゴンの両面を描画する
	context->IASetInputLayout(inputlayout);							// 入力レイアウトを設定する

	DirectX::XMVECTOR color = DirectX::Colors::Yellow;


#ifdef _DEBUG
	// プリミティブ描画を開始する
	batch->Begin();

	// 境界スフィアを描画する
	DX::Draw(batch, *m_boundingSphere, color);
	DX::Draw(batch, *m_boundingOrientedBox, color);
	// プリミティブ描画を終了する
	batch->End();

#endif


}

/// <summary>
/// ボックスの更新
/// </summary>
void OBB::BoxUpdate()
{
	//座標の更新
	m_boundingOrientedBox->Center = GetActor()->GetTransform()->GetRotatePosition() + OffsetPosition();
	auto scale = GetActor()->GetTransform()->GetWorldScale();
	//大きさの更新
	m_boundingOrientedBox->Extents = GetInitialExtents() * scale;
	//回転の更新
	m_boundingOrientedBox->Orientation = GetActor()->GetTransform()->GetWorldRotate();

}

/// <summary>
/// スフィアの更新
/// </summary>
void OBB::SphereUpdate()
{
	//座標の更新
	m_boundingSphere->Center = GetActor()->GetTransform()->GetRotatePosition() + OffsetPosition();
	auto scale = GetActor()->GetTransform()->GetWorldScale();
	//大きさの更新
	m_boundingSphere->Radius = GetInitialRaduis() * std::max({ scale.x,scale.y,scale.z });


}


/// <summary>
/// バウンディングボックスの取得
/// </summary>
/// <returns></returns>
DirectX::BoundingOrientedBox* OBB::GetBoundingOrientedBox()
{
	BoxUpdate();
	return m_boundingOrientedBox.get();
}

/// <summary>
/// バウンディングスフィアの取得
/// </summary>
/// <returns></returns>
DirectX::BoundingSphere* OBB::GetBoundingSphere()
{
	SphereUpdate();
	return m_boundingSphere.get();
}





