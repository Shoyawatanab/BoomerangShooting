#include "pch.h"
#include "InputMessenger.h"

/// <summary>
/// コンストラク
/// </summary>
InputMessenger::InputMessenger()
{
}

/// <summary>
/// デストラクタ
/// </summary>
InputMessenger::~InputMessenger()
{
	
}

/// <summary>
/// 通知を送る
/// </summary>
/// <param name="keyboardState"></param>
void InputMessenger::Notify(const DirectX::Keyboard::State& keyboardState)
{
	// 「観察者リスト」からキーとキーの範囲(開始インデックスと終了インデックス)を取り出す
	for (const auto& keyRange : m_keysRangeList)
	{
		// 観察者が処理すべきキーかどうかを調べる
		if (keyboardState.IsKeyDown(keyRange.first))
		{
			// キーの開始インデックスから終了インデックスまでのインデックス取り出す
			for (auto range = keyRange.second[0].first; range <= keyRange.second[0].second; range++)
			{

				// 観察者の通知関数に押下げられたキーを通知する
				m_keybordList[range].second(m_keybordList[range].first);

			}
		}
	}

}

/// <summary>
/// 登録
/// </summary>
/// <param name="key">キータイプ</param>
/// <param name="function">関数</param>
void InputMessenger::Rigister(const DirectX::Keyboard::Keys& key
	, std::function<void(const DirectX::Keyboard::Keys& key)> function)
{
	m_keybordList.emplace_back(std::make_pair(key, function));

}

void InputMessenger::SortObserverList()
{
	// 「観察者リスト」をキーでソートする
	std::sort(
		m_keybordList.begin(),
		m_keybordList.end(),
		[](const std::pair<DirectX::Keyboard::Keys, std::function<void(const DirectX::Keyboard::Keys& key)>>& a
			, const std::pair<DirectX::Keyboard::Keys, std::function<void(const DirectX::Keyboard::Keys& key)>>& b)
		{
			return a.first < b.first;
		});

}

void InputMessenger::CreateKeyRangeList()
{
	//リストに追加されたものがない場合
	if (m_keybordList.empty())
	{
		return;
	}

	// 開始インデックスを設定する
	size_t  startIndex = 0;
	// 「キー範囲リスト」でデータが存在する場合は「キー範囲リスト」をクリアする
	if (m_keysRangeList.size())
		m_keysRangeList.clear();
	// 「観察者リスト」の開始キーを現在のキーにする
	DirectX::Keyboard::Keys currentKey = m_keybordList[startIndex].first;
	// 「観察者リスト」の開始から終了まで繰り返す
	for (size_t index = 1; index < m_keybordList.size(); index++)
	{
		// 「観察者リスト」のキーと現在のキーが等しくなくなった場合
		if (m_keybordList[index].first != currentKey)
		{
			// キーとキーの範囲(開始インデックスと終了インデックス)を「キー範囲リスト」に追加する
			m_keysRangeList[currentKey].push_back(std::make_pair(startIndex, index - 1));
			// インデックスを開始インデックスに設定する
			startIndex = index;
			// 「観察者リスト」のキーを現在のキーに設定する
			currentKey = m_keybordList[index].first;
		}
	}
	// キーとキーの範囲(開始インデックスと終了インデックス)を「キー範囲リスト」に追加する
	m_keysRangeList[currentKey].push_back(std::make_pair(startIndex, m_keybordList.size() - 1));

}
