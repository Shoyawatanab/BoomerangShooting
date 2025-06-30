#pragma once
#include "GameBase/Component.h"

class AnimationController;

class AnimatorComponent : public Component
{
public:
	//コンストラクタ
	AnimatorComponent(Actor* owner, std::unique_ptr<AnimationController> controller);
	//デストラクタ
	~AnimatorComponent() override ;

	// アップデート
	void Update(const float& deltaTime)override;
	//アニメーションの再生
	void Play(const std::string& animatioName);

	//1回アニメーション実行
	void SetTrigger(const std::string& connectionName);

	//アニメーションの切り替え　対よりも大きい場合のみ変更
	void SetFloat(const std::string& connectionName, const float& value);



private:
	//コントローラー
	std::unique_ptr<AnimationController> m_controller;


};