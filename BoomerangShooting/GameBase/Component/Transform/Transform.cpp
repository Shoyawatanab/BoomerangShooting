#include"pch.h"
#include"Transform.h"

Transform::Transform(Actor* owner)
	:
	Component{owner}
	,m_position{DirectX::SimpleMath::Vector3::Zero}
	,m_scale{DirectX::SimpleMath::Vector3::One}
	,m_rotate{DirectX::SimpleMath::Quaternion::Identity}
	,m_isCompute{false}
	,m_parent{nullptr}
	,m_children{}
{

}

Transform::~Transform()
{

}


/// <summary>
/// ワールド行列取得
/// </summary>
DirectX::SimpleMath::Matrix Transform::GetWorldMatrix()
{
	using namespace DirectX::SimpleMath;

	// 計算フラグが立っている場合計算する
	if (m_isCompute)
	{
		// 大きさ＊回転＊位置の計算順
		m_matrix = Matrix::CreateScale(m_scale);
		m_matrix *= Matrix::CreateFromQuaternion(m_rotate);
		m_matrix *= Matrix::CreateTranslation(m_position);
		m_isCompute = false;
	}

	Matrix worldMatrix = m_matrix;

	// 親がいる場合に、親の行列をかける
	if (m_parent != nullptr)
	{
		worldMatrix *= m_parent->GetWorldMatrix();
	}
	// 行列を返す
	return worldMatrix;
}

/// <summary>
/// ワールドの位置を返す
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldPosition()
{
	using namespace DirectX::SimpleMath;

	Vector3 worldPos = m_position;
	// 親がいる場合、親のポジションを足す
	if (m_parent != nullptr)
	{
		worldPos += m_parent->GetWorldPosition();
	}
	// 位置を返す
	return worldPos;
}

/// <summary>
/// ワールドのスケールを返す
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::GetWorldScale()
{
	using namespace DirectX::SimpleMath;

	Vector3 worldScale = m_scale;
	// 親がいる場合、親の大きさを足す
	if (m_parent != nullptr)
	{
		worldScale += m_parent->GetWorldScale();
	}
	return worldScale;
}

/// <summary>
/// ワールド回転を返す
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Quaternion Transform::GetWorldRotate()
{
	using namespace DirectX::SimpleMath;

	Quaternion worldRotate = m_rotate;
	// 親がいる場合、親の回転をかける
	if (m_parent != nullptr)
	{
		worldRotate *= m_parent->GetWorldRotate();
	}
	return worldRotate;
}

/// <summary>
/// ポジションをセットする
/// </summary>
/// <param name="position"></param>
void Transform::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
	m_isCompute = true;
}

/// <summary>
/// スケールをセットする
/// </summary>
/// <param name="scale"></param>
void Transform::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
	m_isCompute = true;
}

/// <summary>
/// 回転をセットする
/// </summary>
/// <param name="rotate"></param>
void Transform::SetRotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = rotate;
	m_isCompute = true;
}

/// <summary>
/// 位置移動（加算）
/// </summary>
/// <param name="position"></param>
void Transform::Translate(const DirectX::SimpleMath::Vector3& position)
{
	m_position += position;
	m_isCompute = true;
}

/// <summary>
/// スケール変化(加算)
/// </summary>
/// <param name="scale"></param>
void Transform::TransScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale += scale;
	m_isCompute = true;
}

/// <summary>
/// スケール変化(乗算)
/// </summary>
/// <param name="scale"></param>
void Transform::TransScale(const float& scale)
{
	m_scale *= scale;
	m_isCompute = true;
}

/// <summary>
/// 回転(クォータニオン)
/// </summary>
/// <param name="rotate"></param>
void Transform::TransRotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = m_rotate * rotate;
	m_isCompute = true;
}

/// <summary>
/// 回転(軸 , 角度)
/// </summary>
void Transform::TransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	Quaternion quaternion = Quaternion::CreateFromAxisAngle(axis, XMConvertToRadians(angle));
	TransRotate(quaternion);
}

/// <summary>
/// ローカル回転
/// </summary>
void Transform::LocalTransRotate(const DirectX::SimpleMath::Vector3& axis, const float& angle)
{
	using namespace DirectX::SimpleMath;

	Vector3 localAxis = GetLocalAxis(axis);
	TransRotate(localAxis, angle);
}


/// <summary>
/// 軸の方向を返す
/// </summary>
DirectX::SimpleMath::Vector3 Transform::GetLocalAxis(const DirectX::SimpleMath::Vector3& axis)
{
	using namespace DirectX::SimpleMath;

	Vector3 localAxis = Vector3::Transform(axis, m_rotate);
	localAxis.Normalize();
	return localAxis;
}

/// <summary>
/// 親の回転を考慮したポジションを返す
/// </summary>
DirectX::SimpleMath::Vector3 Transform::GetRotatePosition()
{
	using namespace DirectX::SimpleMath;

	if (m_parent == nullptr) 
	{ 
		return m_position; 
	}

	Vector3 distance = m_position * m_parent->m_scale;
	distance = Vector3::Transform(distance, m_parent->GetWorldRotate());
	return m_parent->GetRotatePosition() + distance;
}



/// <summary>
/// 正面ベクトルの取得
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Transform::GetForwardVector()
{
	using namespace DirectX::SimpleMath;

	Vector3 forward = Vector3::Transform(Vector3::Backward, m_rotate);
	forward.Normalize();

	return forward;
}

/// <summary>
/// 親のセット
/// </summary>
/// <param name="parent"></param>
void Transform::SetParent(Transform* parent)
{
	// 親がいない場合
	if (parent == nullptr)
	{
		// 引数がnullで、すでに親がいる場合
		if (m_parent != nullptr)
		{
			// 親の情報から逆算した情報にする
			CalculationRemoveParent();
			// 親から解除
			m_parent->RemoveChild(this);
			m_parent = nullptr;
		}
	}
	else
	{
		// 引数があり、現在の親と違う場合
		if (m_parent != parent)
		{
			if (m_parent != nullptr)
			{
				// 元の親の情報から逆算した情報にする
				CalculationRemoveParent();
			}
			// 親の設定
			m_parent = parent;
			m_parent->SetChild(this);
			CalculationSetParent();
		}
	}
}

/// <summary>
/// 子を取得する
/// </summary>
/// <param name="num">インデックス番号</param>
/// <returns></returns>
Transform* Transform::GetChild(int num)
{
	// 入力されたインデックス番号がサイズより多い場合、nullptrを返す
	if (num >= m_children.size()) 
	{ 
		return nullptr; 
	}
	// 子を返す
	return m_children[num];
}

/// <summary>
/// 自身も含めた子孫トランスフォームを全て返す
/// </summary>
/// <returns>子孫トランスフォーム</returns>
std::vector<Transform*> Transform::GetAllDescendants()
{
	//格納変数
	std::vector<Transform*> transforms;
	//自身も追加
	transforms.push_back(this);
	//子孫ノードを探す
	CollentDescendants(this, transforms);

	return transforms;
}

/// <summary>
/// 子を削除する
/// </summary>
/// <param name="child"></param>
void Transform::RemoveChild(Transform* child)
{
	// 子を探す
	auto searchChiled = std::find(m_children.begin(), m_children.end(), child);

	if (searchChiled != m_children.end())
	{
		// 子供たちのなかから、特定の子を削除
		m_children.erase(searchChiled);
	}
}

/// <summary>
/// 親を設定した際に、情報を変更する
/// </summary>
void Transform::CalculationSetParent()
{
	using namespace DirectX::SimpleMath;

	// 位置の移動
	m_position -= m_parent->m_position;
	// スケールの変換
	m_scale = Vector3
	{
		m_scale.x / m_parent->m_scale.x,
		m_scale.y / m_parent->m_scale.y,
		m_scale.z / m_parent->m_scale.z,
	};
	// 回転の変換
	Quaternion invers = m_parent->m_rotate;
	invers.Inverse(invers);
	m_rotate *= invers;
	// 回転移動
	DirectX::SimpleMath::Vector3 dire = m_position;
	dire = Vector3(
		dire.x / m_parent->m_scale.x,
		dire.y / m_parent->m_scale.y,
		dire.z / m_parent->m_scale.z
	);
	// 行列の変換
	Matrix mat = Matrix::CreateFromQuaternion(invers);
	m_position = Vector3::Transform(dire, mat);
	// 計算終了
	m_isCompute = true;
}

/// <summary>
/// 親を解除した際の情報変更
/// </summary>
void Transform::CalculationRemoveParent()
{
	using namespace DirectX::SimpleMath;

	// 回転取得
	Quaternion invers = m_parent->GetWorldRotate();
	// 位置取得
	Vector3 dire = m_position;
	dire = Vector3(
		dire.x * m_parent->m_scale.x,
		dire.y * m_parent->m_scale.y,
		dire.z * m_parent->m_scale.z
	);
	// 行列の取得
	Matrix mat = Matrix::CreateFromQuaternion(invers);
	// 位置を変更
	m_position = Vector3::Transform(dire, mat);

	m_position += m_parent->m_position;
	m_scale = Vector3(
		m_scale.x * m_parent->m_scale.x,
		m_scale.y * m_parent->m_scale.y,
		m_scale.z * m_parent->m_scale.z
	);

	m_rotate *= m_parent->m_rotate;
	m_isCompute = true;
}

/// <summary>
/// 再帰的に子孫を返す
/// </summary>
/// <param name="node">どのトランスフォームか</param>
/// <param name="tranforms">格納変数</param>
void Transform::CollentDescendants(Transform* node, std::vector<Transform*>& tranforms)
{
	//子ノードの
	for (auto& child : node->GetAllChild())
	{
		//トランスフォームに格納
		tranforms.push_back(child);
		//子の子を探して返す
		CollentDescendants(child, tranforms);
	}

}
