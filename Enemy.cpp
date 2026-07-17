#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Engine\\Input.h"

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
}

//更新
void Enemy::Update()
{
	transform_.position_.z += 0.1f;
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
}
