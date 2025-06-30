/*
* コンポジットパターンの根のインターフェース
*/
#pragma once
#include "Game/Interface/ICharacter.h"


class IComposite : public ICharacter
{
public:
	//デストラクタ
	virtual ~IComposite() = default;
	//子要素の追加
	virtual void AddChild(std::unique_ptr<ICharacter> parts) = 0;
	//子要素の削除
	//virtual void DeleteChild(std::unique_ptr<ICharacter> parts) = 0;
};
