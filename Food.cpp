#include "Food.h"
#include "Engine/Model.h"

Food::Food(GameObject* parent)
	:GameObject(parent, "Food"), type_(FOODTYPE_NORMAL), hModel_(-1), score_(0)
{
}

Food::~Food()
{
}

void Food::Initialize()
{
	SphereCollider* collider = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 0.3f);
	AddCollider(collider);
}

void Food::Update()
{
	if (type_ == FoodType::FOODTYPE_POWER)
	{
		transform_.rotate_.y += 1.0f;
	}
}

void Food::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Food::Release()
{
}

void Food::SetFoodType(FoodType type)
{
	type_ = type;

	if (type_ == FoodType::FOODTYPE_NORMAL)
	{
		hModel_ = Model::Load("Feed.fbx");
		score_ = 1;
	}

	else if (type_ == FoodType::FOODTYPE_POWER)
	{
		hModel_ = Model::Load("FeedP.fbx");

		transform_.scale_.x *= 2.0f;
		transform_.scale_.y *= 2.0f;
		transform_.scale_.z *= 2.0f;

		score_ = 5;
	}

}

void Food::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		KillMe();  //自分も消す
		score_++;
	}
}
