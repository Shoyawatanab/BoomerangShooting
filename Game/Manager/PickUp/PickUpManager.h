/*
	クラス名     : PickUpManager
	説明         : 拾う動作マネージャー
	補足・注意点 :
*/
#pragma once
#include <unordered_map>
#include "GameBase/WataLib/Singleton.h"

class PickerComponent;
class PickableComponent;

class PickUpManager
{
public:
	//拾う種類
	enum  class PickUpType
	{
		PLAYER_PICKUP_WEAPON            //プレイヤが武器を拾う
	};


public:
	//コンストラク
	PickUpManager();
	//デストラクタ
	~PickUpManager();
	//更新処理
	void Update(const float& deltaTime);

	//回収の実行
	void TryPickUp(PickerComponent* comp);


	//回収者の追加
	void AddPicker(PickUpType type, PickerComponent* comp);
	//拾われる物の追加
	void AddPickable(PickUpType type, PickableComponent* comp);

private:

	//回収可能か
	PickableComponent* CheckPickUp(PickerComponent* picker , std::vector<PickableComponent*> picktables);

private:

	//格納配列　　
	std::unordered_map<PickUpType, std::pair<PickerComponent*, std::vector<PickableComponent*>>> m_list;


};