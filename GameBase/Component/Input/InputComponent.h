#pragma once
#include "GameBase/Component.h"
#include "GameBase/Actor.h"

class InputComponent : public Component
{
public:
	//コンストラク
	InputComponent(Actor* owner);
	//デストラクタ
	~InputComponent();

	//登録
	void Rigister(std::vector<DirectX::Keyboard::Keys> keys
		, std::function<void(const DirectX::Keyboard::Keys& key)> function);

private:

	//呼び出し関数
	std::function<void(const DirectX::Keyboard::Keys& key)> m_function;


};