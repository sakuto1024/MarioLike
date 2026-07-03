#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"


Ground::Ground(GameObject* parent)
	:GameObject(parent), hModel_(-1)
{
}

void Ground::Initialize()
{
	hModel_ = Model::Load("uvGround.fbx");
	Model::SetAnimFrame(hModel_, 0, 59, 1.0);


	/*transform_.position_.z += 100.0f;
	transform_.position_.y += -20.0f;
	transform_.position_.x += 30.0f;
	transform_.rotate_.x += -90.0f;*/

	
}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Ground::Release()
{
}
