#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

class Text;
class Food;

//テストシーンを管理するクラス
class TestScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TestScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void AddScore(int scr) { score_  += scr; }
	void DecMaxFoodP(int decF) { maxFoodP_ -= decF; }
	void DecMaxFoodN(int decF) { maxFoodN_ -= decF; }

private:
	Text* pText_;
	int maxFoodP_;
	int maxFoodN_;
	int score_;
};