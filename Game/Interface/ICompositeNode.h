#pragma once
#include "Game/Interface/IBehaviorNode.h"


class ICompositeNode : public IBehaviorNode
{
public:

	//ƒm[ƒh‚Ì’Ç‰Á
	virtual void AddNode(std::unique_ptr<IBehaviorNode> node) = 0;

};

