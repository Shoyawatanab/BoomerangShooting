#pragma once
#include"GameBase/Component.h"

class Transform : public Component
{
public:
	// 自分自身の位置を返す
	DirectX::SimpleMath::Vector3 GetWorldPosition();
	// 自分自身の大きさを返す
	DirectX::SimpleMath::Vector3 GetWorldScale();
	// 自分自身の回転を返す
	DirectX::SimpleMath::Quaternion GetWorldRotate();
	// 自分自身の行列を返す
	DirectX::SimpleMath::Matrix GetWorldMatrix();

	// 位置の取得
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	//位置のセット
	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
	// 大きさの取得
	DirectX::SimpleMath::Vector3 GetScale() const { return m_scale; }
	//大きさのセット
	void SetScale(const DirectX::SimpleMath::Vector3& scale);
	// 回転の取得
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	//回転のセット
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate);

	// 行列の取得
	DirectX::SimpleMath::Matrix GetMatrix() const { return m_matrix; }


	// 位置の移動（加算)
	void Translate(const DirectX::SimpleMath::Vector3& pos);
	// 大きさの変更(加算)
	void TransScale(const DirectX::SimpleMath::Vector3& scale);
	// 大きさの変更(乗算)
	void TransScale(const float& scale);
	// 回転の変更
	void TransRotate(const DirectX::SimpleMath::Quaternion& rotate);
	// 軸と角度で回転する
	void TransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle);
	// ローカル軸と角度で回転
	void LocalTransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle);
	// 自身の姿勢に対する軸の方向を返す
	DirectX::SimpleMath::Vector3 GetLocalAxis(const DirectX::SimpleMath::Vector3& axis);
	// 回転を考慮した位置
	DirectX::SimpleMath::Vector3 GetRotatePosition();
	//正面ベクトルの取得
	DirectX::SimpleMath::Vector3 GetForwardVector();

	// 親をセットする
	void SetParent(Transform* parent);
	//親を取得
	Transform* GetParent() { return m_parent; }

	// 子の取得
	Transform* GetChild(int num);
	// 全ての子供を返す
	std::vector<Transform*> GetAllChild() { return m_children; }
	/// 自身も含めた子孫トランスフォームを全て返す
	std::vector<Transform*> GetAllDescendants();

public:
	// コンストラクタ、
	Transform(Actor* owner);
	//デストラクタ
	~Transform();

private:
	// 子のセット
	void SetChild(Transform* child) { m_children.push_back(child); }
	// 子を消去
	void RemoveChild(Transform* child);
	// 親設定時の情報変更
	void CalculationSetParent();
	// 親解除時に情報変更
	void CalculationRemoveParent();

	//再帰敵に子を返す関数
	void CollentDescendants(Transform* node, std::vector<Transform*>& tranforms);

private:
	// 位置
	DirectX::SimpleMath::Vector3 m_position;
	// 大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	// 回転
	DirectX::SimpleMath::Quaternion m_rotate;
	// 行列
	DirectX::SimpleMath::Matrix m_matrix;
	// 行列計算フラグ
	bool m_isCompute;
	// 親
	Transform* m_parent;
	// 子
	std::vector<Transform*> m_children;
};