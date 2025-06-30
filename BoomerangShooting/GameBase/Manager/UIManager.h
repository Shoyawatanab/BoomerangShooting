#pragma once

class ButtonComponent;


class UIManager
{
public:
	//コンストラク
	UIManager();
	//デストラクタ
	~UIManager();

	//更新処理
	void Update(const float& deltaTime);

	void AddButtomComponent(ButtonComponent* buttom);

private:
	//範囲内か
	bool CheckInRange(const DirectX::SimpleMath::Vector2& mousePosition,ButtonComponent* buttom);

private:

	std::vector<ButtonComponent*> m_buttom;

};


