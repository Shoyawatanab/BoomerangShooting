#include "pch.h"
#include "Json.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

/// <summary>
/// コンストラクタ
/// </summary>
WataLib::Json::Json()
	:
	m_stageParamter{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
WataLib::Json::~Json()
{
}


/// <summary>
/// ステージデータの読み込み
/// </summary>
/// <param name="fileName">ファイル名</param>
/// <returns>ステージデータ</returns>
WataLib::Json::StageData WataLib::Json::LoadStageDatas(const std::wstring& fileName)
{

	std::ifstream file(L"Resources/Dates/Stages/" + fileName + L".json");

	//ファイルが開けないとき
	if (!file.is_open())
	{
		throw std::runtime_error("jsonファイルが開けません");
	}

	//ファイルの内容をJSONオブジェックとしてパース
	json data = json::parse(file);

	StageData stageData;

	//必要データの取得

	stageData.BoomerangCount = data["BoomerangCount"];



	//ステージ情報の保存配列を作成
	std::vector<ObjectData> objectData;

	//StageObject[](ピンク色)内のデータの{}(青色)の要素だけ回す
	for (const auto& item : data["StageObject"])
	{
		//ステージデータ変数
		ObjectData object;
		//kindsの要素の値を代入
		object.ModelName = item["kinds"];


		//BoundingSphereRadiusがあるか
		if (item.contains("BoundingSphereRadius"))
		{
			//BoundingSphereRadiusの要素の値を代入
			object.BoundingSphereRadius = item["BoundingSphereRadius"];
		}
		//なければ
		else
		{
			object.BoundingSphereRadius = 0.0f;
		}

		//Positionがあるか
		if (item.contains("Position"))
		{
			//Positionの要素を代入
			object.Position = DirectX::SimpleMath::Vector3(
				item["Position"]["x"],           //Positionの要素のxの要素を代入x値
				item["Position"]["y"],           //Positionの要素のxの要素を代入y値
				item["Position"]["z"]            //Positionの要素のxの要素を代入z値
			);
		}
		//なければ
		else
		{
			object.Position = DirectX::SimpleMath::Vector3::Zero;
		}

		//Scaleがあるか
		if (item.contains("Scale"))
		{
			//Scaleの要素を代入
			object.Scale = DirectX::SimpleMath::Vector3(
				item["Scale"]["x"],             //Scaleの要素のxの要素を代入
				item["Scale"]["y"],             //Scaleの要素のyの要素を代入
				item["Scale"]["z"]              //Scaleの要素のzの要素を代入
			);
		}
		//なければ
		else
		{
			object.Scale = DirectX::SimpleMath::Vector3::Zero;
		}

		//Rotationがあるか
		if (item.contains("Rotation"))
		{
			//Rotationの要素を代入
			object.Rotation = DirectX::SimpleMath::Vector3(
				item["Rotation"]["x"],          //Rotationの要素のxの要素を代入
				item["Rotation"]["y"],          //Rotationの要素のyの要素を代入
				item["Rotation"]["z"]           //Rotationの要素のzの要素を代入
			);
		}
		//なければ
		else
		{
			object.Rotation = DirectX::SimpleMath::Vector3::Zero;
		}

		
		//１つのステージデータを代入
		objectData.push_back(object);

	}


	//オブジェクトデータの登録
	stageData.ObjectDatas = objectData;


	return stageData;

}

/// <summary>
/// アニメーションデータの読み込み
/// </summary>
/// <param name="fileName">ファイル名</param>
/// <returns>アニメーションデータ</returns>
std::unordered_map<std::string, WataLib::Json::AnimationData> WataLib::Json::LoadAnimationData(const std::wstring& fileName)
{
	std::ifstream file(L"Resources/Dates/Animation/" + fileName + L".json");

	//ファイルが開けないとき
	if (!file.is_open())
	{
		throw std::runtime_error("jsonファイルが開けません");
	}

	//ファイルの内容をJSONオブジェックとしてパース
	json data = json::parse(file);


	//アニメーションの種類
	std::string animationType = data["AnimationType"];

	//アニメーションのトータル時間
	float totalTime = data["AnimationTime"];

	//アニメーションのスピード
	float speed = data["AnimationSpeed"];

	//ループ再生かどうか
	bool isLoop = data["Loop"];

	//パーツごとにアニメーションを分けるための格納変数
	std::unordered_map<std::string, std::vector<AnimationKeyFram>> partsKeyFrame;

	

	//KeyFrame[](ピンク色)内のデータの{}(青色)の要素だけ回す
	for (const auto& frameData : data["KeyFrame"])
	{
		
		//フレームの時間の取得
		float frameTime = frameData["FreamTime"];



		//部位ごとの情報の取得
		for (const auto& partsData : frameData["Parts"])
		{
			std::string partsName = partsData["PartName"];

			AnimationKeyFram keyFrame;

			keyFrame.Time = frameTime;

			//Positionがあるか
			if (partsData.contains("Position"))
			{
				//Positionの要素を代入
				keyFrame.Position = DirectX::SimpleMath::Vector3(
					partsData["Position"]["x"],           //Positionの要素のxの要素を代入x値
					partsData["Position"]["y"],           //Positionの要素のxの要素を代入y値
					partsData["Position"]["z"]            //Positionの要素のxの要素を代入z値
				);
			}



			//Positionがあるか
			if (partsData.contains("Rotation"))
			{
				//Positionの要素を代入
				keyFrame.Rotation = DirectX::SimpleMath::Vector3(
					partsData["Rotation"]["x"],           //Positionの要素のxの要素を代入x値
					partsData["Rotation"]["y"],           //Positionの要素のxの要素を代入y値
					partsData["Rotation"]["z"]            //Positionの要素のxの要素を代入z値
				);
			}


			partsKeyFrame[partsName].push_back(keyFrame);
			
		}
	}

	//パーツごとのアニメーションを
	std::unordered_map<std::string, AnimationData> animations;

	for (auto& parts : partsKeyFrame)
	{

		std::string partsName = parts.first;

		std::vector<AnimationKeyFram> keyFrame = parts.second;

		animations[partsName].FramDatas = keyFrame;
		animations[partsName].TotalTime = totalTime;
		animations[partsName].Speed = speed;
		animations[partsName].IsLoop = isLoop;


	}

	return animations;
}
