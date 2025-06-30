#pragma once



class IFade
{
public:

	virtual ~IFade() = default;

	//XVˆ—
	virtual bool Update(const float& deltaTime) = 0;
	//•`‰æ
	virtual void Render() = 0;
	//“ü‚Á‚½
	virtual void Enter() = 0;
	//”²‚¯‚½
	virtual void Exit() = 0;

};