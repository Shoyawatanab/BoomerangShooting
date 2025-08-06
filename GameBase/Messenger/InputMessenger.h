#pragma once
#include "GameBase/WataLib/Singleton.h"


class InputMessenger : public Singleton<InputMessenger>
{
	friend class Singleton<InputMessenger>;
public:
	//コンストラク
	InputMessenger();
	//デストラクタ
	~InputMessenger()override;
	//通知を送る
	void Notify(const DirectX::Keyboard::State& keyboardState);

	//登録
	void Rigister(const DirectX::Keyboard::Keys& key, std::function<void(const DirectX::Keyboard::Keys& key)> function);


	// 観察者リストをソートする
	void SortObserverList();
	//  キー範囲リストを生成する
	void CreateKeyRangeList();


private:

	// キーボードリスト
	std::vector<std::pair<DirectX::Keyboard::Keys, std::function<void(const DirectX::Keyboard::Keys& key)>>> m_keybordList;
	// キー範囲リスト(開始インデックスと終了インデックス)
	std::unordered_map<DirectX::Keyboard::Keys, std::vector<std::pair<size_t, size_t>>> m_keysRangeList;


};
