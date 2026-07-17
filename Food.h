#pragma once
#include "Engine/GameObject.h"

enum FoodType
{
	FOODTYPE_NORMAL,
	FOODTYPE_POWER,
	FOODTYPE_MAX
};

class Food : public GameObject
{
public:
	Food(GameObject* parent);
	~Food();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetFoodType(FoodType type);
	void OnCollision(GameObject* pTarget) override;

private:
	FoodType type_;
	int hModel_;
	int score_;
};

