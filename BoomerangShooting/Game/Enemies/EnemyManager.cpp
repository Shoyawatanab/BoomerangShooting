#include "pch.h"
#include "EnemyManager.h"
#include "Game/Enemies/Enemys.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/GlobalGameData.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="player">プレイヤ</param>
EnemyManager::EnemyManager(Scene* scene,Player* player)
	:
	Actor(scene)
	,m_player{player}
{
	using namespace DirectX::SimpleMath;

	//ステージデータの読み込み
	LoadData();

}

/// <summary>
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{
}

/// <summary>
/// 敵の死亡
/// </summary>
/// <param name="enemy"></param>
void EnemyManager::DeathEnemy(Actor* actor)
{
	//探す
	auto enemy = std::find(m_enemys.begin(), m_enemys.end(), actor);
	
	//いれば
	if (enemy != m_enemys.end())
	{
		//削除
		m_enemys.erase(enemy);
	}



	//すべての敵を倒したら
	if (m_enemys.empty())
	{
		//リザルトシーンに変更の通知
		GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_RESULT_SCENE);

		FadeManager::GetInstance()->StartFadeIn();

	}



}


/// <summary>
/// ステージデータの読み込み
/// </summary>
void EnemyManager::LoadData()
{

	using namespace DirectX::SimpleMath;

	using json = nlohmann::json;


	//ステージ番号の取得
	int stageNumber = GlobalGameData::GetInstance()->GetSelectStateNumber();


	std::ifstream file(L"Resources/Json/Stage/Stage" + std::to_wstring(stageNumber) + L"/Enemy.json");

	//ファイルが開けないとき
	if (!file.is_open())
	{
		throw std::runtime_error("jsonファイルが開けません");
	}

	//ファイルの内容をJSONオブジェックとしてパース
	json data = json::parse(file);

	//StageObject[](ピンク色)内のデータの{}(青色)の要素だけ回す
	for (const auto& item : data["StageObject"])
	{

		//kindsの要素の値を代入
		std::string kinds = item["kinds"];

		if (kinds == "BossEnemy")
		{
			int a = 0;
		}

		//Positionの要素を代入
		Vector3 position;

		//Positionがあるか
		if (item.contains("Position"))
		{
			//Positionの要素を代入
			position = Vector3(
				item["Position"]["x"],           //Positionの要素のxの要素を代入x値
				item["Position"]["y"],           //Positionの要素のxの要素を代入y値
				item["Position"]["z"]            //Positionの要素のxの要素を代入z値
			);
		}
		//なければ
		else
		{
			position = DirectX::SimpleMath::Vector3::Zero;
		}

		Vector3 scale;

		//Scaleがあるか
		if (item.contains("Scale"))
		{
			//Scaleの要素を代入
			scale = Vector3(
				item["Scale"]["x"],             //Scaleの要素のxの要素を代入
				item["Scale"]["y"],             //Scaleの要素のyの要素を代入
				item["Scale"]["z"]              //Scaleの要素のzの要素を代入
			);
		}
		//なければ
		else
		{
			scale = Vector3::Zero;
		}

		Quaternion rotation;

		//Rotationがあるか
		if (item.contains("Rotation"))
		{
			//Rotationの要素を代入
			rotation = Quaternion::CreateFromYawPitchRoll(
				item["Rotation"]["y"],          
				item["Rotation"]["x"],          
				item["Rotation"]["z"]           
			);
		}
		//なければ
		else
		{
			rotation = Quaternion::Identity;
		}



		if (kinds == "BossEnemy")
		{
			//ボス敵の作成
			auto boss = GetScene()->AddActor<BossEnemy>(GetScene(),  scale, position, rotation, m_player);
			boss->SetEnemyManager(this);
			m_enemys.push_back(boss);


		}
		else if (kinds == "BirdEnemy")
		{
			//鳥敵の作成
			auto bird = GetScene()->AddActor<BirdEnemy>(GetScene(), scale, position, rotation, m_player);
			bird->SetEnemyManager(this);
			m_enemys.push_back(bird);


		}


	}



}
