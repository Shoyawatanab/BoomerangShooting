#include "pch.h"
#include "InputComponent.h"
#include "GameBase/Messenger/InputMessenger.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="owner">所有者</param>
InputComponent::InputComponent(Actor* owner)
	:
	Component(owner)
{
}

/// <summary>
/// デストラクタ
/// </summary>
InputComponent::~InputComponent()
{
}

/// <summary>
/// 登録
/// </summary>
/// <param name="keys">登録キー配列</param>
/// <param name="function">呼び出す関数</param>
void InputComponent::Rigister(std::vector<DirectX::Keyboard::Keys> keys
	, std::function<void(const DirectX::Keyboard::Keys& key)> function)
{
	//Messengerの取得
	auto messenger = InputMessenger::GetInstance();


	for (auto key : keys)
	{
		messenger->Rigister(key, function);
	}

}
