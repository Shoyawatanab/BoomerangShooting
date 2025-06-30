#include "pch.h"
#include "RigidbodyManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
RigidbodyManager::RigidbodyManager()
	:
	m_rigidbody{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
RigidbodyManager::~RigidbodyManager()
{
	m_rigidbody.clear();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"経過時間></param>
void RigidbodyManager::Update(const float& deltaTime)
{
	//リジットボディーの更新
	for (auto& rigidbody : m_rigidbody)
	{
		if (!rigidbody->GetActive())
		{
			continue;
		}

		rigidbody->Update(deltaTime);
	}

}

/// <summary>
/// リジットボディーの追加
/// </summary>
/// <param name="rigidbody"></param>
void RigidbodyManager::AddRigidbody(RigidbodyComponent* comp)
{

	auto rigidbody = std::find(m_rigidbody.begin(), m_rigidbody.end(), comp);

	if (rigidbody == m_rigidbody.end())
	{
		m_rigidbody.push_back(std::move(comp));

	}
}

/// <summary>
/// リジットボディーの削除
/// </summary>
/// <param name="rigidbody"></param>
void RigidbodyManager::RemoveRigidbody(RigidbodyComponent* comp)
{

	auto rigidbody = std::find(m_rigidbody.begin(), m_rigidbody.end(), comp);

	if (rigidbody != m_rigidbody.end())
	{

		m_rigidbody.erase(rigidbody);

	}


}
