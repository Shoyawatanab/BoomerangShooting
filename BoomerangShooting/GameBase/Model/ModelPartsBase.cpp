#include "pch.h"
#include "ModelPartsBase.h"
#include "GameBase/Component/Components.h"




ModelPartsBase::ModelPartsBase(Scene* scene, const std::string& partsName, const std::string& modelName)
	:
	Actor(scene)
	, m_partsName{ partsName }
	,m_parent{}
{

	//コンポーネントの追加
	AddComponent<ModelComponent>(this, modelName);
	
}

/// <summary>
/// デストラクタ
/// </summary>
ModelPartsBase::~ModelPartsBase()
{
}

/// <summary>
/// 親の登録
/// </summary>
/// <param name="parent">親</param>
void ModelPartsBase::SetParent(ModelPartsBase* parent)
{
	//親がいない場合
	if (parent == nullptr)
	{
		//親がいる場合
		if (m_parent != nullptr)
		{
			//親からの解除
			m_parent->RemoveChild(this);
			m_parent = nullptr;
		}
		//トランスフォームも親の登録をする
		GetTransform()->SetParent(nullptr);

	}
	else
	{
		//現在と違う親の場合
		if (m_parent != parent)
		{
			//親の設定
			m_parent = parent;
			m_parent->SetChild(this);
		}
		//トランスフォームも親の登録をする
		GetTransform()->SetParent(parent->GetTransform());

	}


}

/// <summary>
/// 自身も含めた子孫モデルを全て返す
/// </summary>
/// <returns></returns>
std::vector<ModelPartsBase*> ModelPartsBase::GetAllDescendants()
{
	//格納変数
	std::vector<ModelPartsBase*> ModelPartsBases;
	//自分自身も追加する
	ModelPartsBases.push_back(this);
	//子孫モデルを探す
	CollentDescendants(this, ModelPartsBases);

	return ModelPartsBases;
}

/// <summary>
/// 子の削除
/// </summary>
/// <param name="child">子</param>
void ModelPartsBase::RemoveChild(ModelPartsBase* child)
{

	//子を探す
	auto serchChild = std::find(m_child.begin(), m_child.end(), child);

	//あれば
	if (serchChild != m_child.end())
	{
		//子の削除
		m_child.erase(serchChild);

	}


}

/// <summary>
/// 再帰的に子孫モデルを返す
/// </summary>
/// <param name="node"></param>
/// <param name="ModelPartsBases"></param>
void ModelPartsBase::CollentDescendants(ModelPartsBase* node, std::vector<ModelPartsBase*>& ModelPartsBases)
{
	//子ノード
	for (auto& child : node->GetAllChild())
	{
		//トランスフォームに格納
		ModelPartsBases.push_back(child);
		//子の子を探して返す
		CollentDescendants(child, ModelPartsBases);
	}

}






