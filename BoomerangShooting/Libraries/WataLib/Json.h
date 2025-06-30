#pragma once
#include <unordered_map>
#include <optional>

namespace WataLib
{
	class Json
	{

	public:

//ステージ情報のJson読み込み専用構造体

		struct ObjectData
		{
			std::string ModelName;
			DirectX::SimpleMath::Vector3 Position;
			DirectX::SimpleMath::Vector3 Scale;
			DirectX::SimpleMath::Vector3 Rotation;
			float BoundingSphereRadius;
		};

		struct StageData
		{
			int BoomerangCount;
			std::vector<ObjectData> ObjectDatas;
		};



//アニメーションのJson読み込み専用構造体

		struct AnimationKeyFram
		{
			float Time;                                //経過時間
			std::optional<DirectX::SimpleMath::Vector3>  Scale ;
			std::optional< DirectX::SimpleMath::Vector3> Position;	    //経過時間に対しての座標
			std::optional< DirectX::SimpleMath::Vector3> Rotation; 		//経過時間に対しての回転

		};

		struct AnimationData
		{
			float TotalTime;                              //アニメーション全体の時間
			float Speed;								  //アニメーションの進行スピード
			bool IsLoop;								  //1アニメーションをループさせるか
			std::vector<AnimationKeyFram> FramDatas;	  //キーフレームの情報　時間順に並んでいるものとする

		};

//

	public:
		//コンストラクタ
		Json();
		//デストラクタ
		~Json();
		//ステージ情報の読み込み
		StageData LoadStageDatas(const std::wstring& fileName);
		//アニメーションデータの読み込み
		std::unordered_map<std::string, AnimationData> LoadAnimationData(const std::wstring& fileName);

	private:
		//ステージ情報のパラメーター
		std::vector<StageData> m_stageParamter;

		

	};
}

/*Jsonファイルについて

	"A" : [
		"B" : "Name",
		"C" : : {
			"D" : 0,
			"E" : 1
		}
	]
	
	Aの要素 BとC
	Bの要素 Name
	Cの要素 DとE
	Dの要素 0
	Eの要素 1

	{}中のものが要素となり要素を参照して代入したりしている
	要素を参照することで改行してもしなくてもどっちでもよくなる


*/