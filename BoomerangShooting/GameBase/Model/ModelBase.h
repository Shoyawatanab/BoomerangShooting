#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Model/ModelPartsBase.h"

class ModelBase : public Actor
{
public:
	//パーツの取得
	std::unordered_map<std::string, ModelPartsBase*>& GetParts() { return m_parts; }

public:
	//コンストラクタ
	ModelBase(Scene* scene);
	//デストラクタ
	~ModelBase();

	//パーツの登録
	void AddParts(std::vector<ModelPartsBase*> partss);

private:

	//パーツ
	std::unordered_map<std::string, ModelPartsBase*> m_parts;

};