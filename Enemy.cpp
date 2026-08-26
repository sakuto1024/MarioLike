#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Engine\\Input.h"
#include "Ground.h"
#include <vector>

namespace
{
	XMVECTOR E_MOVE[4] = {
	XMVectorSet(0, 0, 1, 0),
	XMVectorSet(0, 0, -1, 0),
	XMVectorSet(-1, 0, 0, 0),
	XMVectorSet(1, 0, 0, 0)
	};

	float E_ANGLE[4] = { 180.0f, 0.0f, 90.0f, 270.0f };

}


//コンストラクタ
Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1)
{
}

//初期化
void Enemy::Initialize()
{
	hModel_ = Model::Load("Slime.fbx");
	Model::SetAnimFrame(hModel_, 0, 59, 1.0);

	transform_.position_.y += 5.0f;

	eDirection_ = ENEMY_DIRECTION::ENEMY_UP;
}

//更新
void Enemy::Update()
{
	//transform_.position_.z += 0.1f;

	switch (eState_)
	{
	case ENEMY_IDLE:
		IdleUpdate();
		break;

	case ENEMY_WALK:
		WalkUpdate();
		break;

	case ENEMY_TURN:
		TurnUpdate();
		break;

	case ENEMY_CHASE:
		ChaseUpdate();
		break;
	}

	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	XMVECTOR move = XMVectorSet(0, 0, 0, 0);
	const float SPEED = 0.1;

	move = E_MOVE[eDirection_];

	pos = pos + SPEED * move;
	XMStoreFloat3(&transform_.position_, pos);

	using std::vector;
	vector<vector<int>> gmap = ground_->GetMapData();

	XMFLOAT3 wPos = { -20.0f, 0.0f, 20.0f };

	int mapX = (transform_.position_.x - wPos.x) / 4;
	int mapZ = (-transform_.position_.z + wPos.z) / 4;

	if (gmap[mapZ][mapX] == 1)
	{
		pos = pos - SPEED * move;
		XMStoreFloat3(&transform_.position_, pos);
		eState_ = ENEMY_STATE::ENEMY_TURN;
	}
}

void Enemy::IdleUpdate()
{

}

void Enemy::WalkUpdate()
{
}

void Enemy::TurnUpdate()
{
}

void Enemy::ChaseUpdate()
{
}

//描画
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
	this->KillMe();
}
