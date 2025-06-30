/*
	パーツモデルの基底クラス　どんなパーツモデルでも継承する
*/

#pragma once
#include "GameBase/Actor.h"


class ModelPartsBase : public Actor
{
public:

	//名前の取得
	std::string  GetPartsName() const { return m_partsName; }
	//全てのパーツの取得
	const std::vector<ModelPartsBase*>& GetAllChild() { return m_child; }

	void SetParent(ModelPartsBase* parent);

	//自身も含めた子孫モデルを全てを返す
	std::vector<ModelPartsBase*> GetAllDescendants();

private:
	
	void SetChild(ModelPartsBase* child) { m_child.push_back(child); };
	//子の削除
	void RemoveChild(ModelPartsBase* child);

	//再帰敵に子を返す関数
	void CollentDescendants(ModelPartsBase* node, std::vector<ModelPartsBase*>& ModelPartsBase);


public:

	//コンストラクタ
	ModelPartsBase(Scene* scene, const std::string& partsName, const std::string& modelName);
	//デストラクタ
	~ModelPartsBase();



private:
	//パーツ名
	std::string m_partsName;
	//子オブジェクト
	std::vector<ModelPartsBase*>m_child;
	//親モデル
	ModelPartsBase* m_parent;

};
