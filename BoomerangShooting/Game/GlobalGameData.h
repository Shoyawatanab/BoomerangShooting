#pragma once
#include "Libraries/WataLib/Singleton.h"

class GlobalGameData : public Singleton<GlobalGameData>
{
	friend class Singleton<GlobalGameData>;
public:

	//選択ステージ番号のセット
	void SetSelectStateNumber(int number) { m_selectStageNumber = number; }
	//ステージ番号の取得
	int GetSelectStateNumber() const { return m_selectStageNumber; }
	//クリアタイムの取得
	float GetClearTime() const { return m_clearTime; }
	//クリアタイムの加算
	void AddClearTime(const float& time) { m_clearTime += time; }
	//クリアタイムのリセット
	void ResetClearTime() { m_clearTime = 0.0f; };
public:
	//コンストラク
	GlobalGameData();
	//デストラクタ
	~GlobalGameData() override;


private:

	//選ばれたステージ番号
	int m_selectStageNumber;
	//クリアタイム
	float m_clearTime;

};