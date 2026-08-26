#pragma once
#include "Engine/GameObject.h"

class Ground;


//テストシーンを管理するクラス
class Enemy : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	void IdleUpdate();
	void WalkUpdate();
	void TurnUpdate();
	void ChaseUpdate();

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void SetGround(Ground* ground) { ground_ = ground; }

private:
	int hModel_;

	

	enum ENEMY_STATE
	{
		ENEMY_IDLE,
		ENEMY_WALK,
		ENEMY_TURN,
		ENEMY_CHASE,
		ENEMY_STATE_MAX
	};
	ENEMY_STATE eState_;

	enum ENEMY_DIRECTION
	{
		ENEMY_UP,
		ENEMY_DOWN,
		ENEMY_LEFT,
		ENEMY_RIGHT,
		ENEMY_DIRECTION_MAX
	};
	ENEMY_DIRECTION eDirection_;

	Ground* ground_;
};