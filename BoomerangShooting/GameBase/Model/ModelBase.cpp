#include "pch.h"
#include "ModelBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
ModelBase::ModelBase(Scene* scene)
	:
	Actor(scene)
	,m_parts{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
ModelBase::~ModelBase()
{
	//クリア
	m_parts.clear();

}

/// <summary>
/// パーツの登録
/// </summary>
/// <param name="partss">パーツ配列</param>
void ModelBase::AddParts(std::vector<ModelPartsBase*> partss)
{
	for (auto& parts : partss)
	{
		//パーツ名の取得
		auto name = parts->GetPartsName();
		//登録されたパーツ名があるか
		auto sertchParts = m_parts.find(name);
		//あれば
		if (sertchParts != m_parts.end())
		{
			continue;
		}

		m_parts[name] = parts;


	}

}
