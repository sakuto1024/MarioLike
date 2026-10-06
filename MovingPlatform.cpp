#include "MovingPlatform.h"
#include "Engine/Model.h"

MovingPlatform::MovingPlatform(GameObject* parent)
    :GameObject(parent, "MovingPlatform"), hModel_(-1), speed_(0.1f), moveRange_(10.0f), isMoveRight_(false), pos_(0.0f, 0.0f, 0.0f)
{
}

void MovingPlatform::Initialize()
{
    hModel_ = Model::Load("BlueBrick.fbx");

    startPos_ = transform_.position_;
    oldPos_ = transform_.position_;
}

void MovingPlatform::Update()
{
    pos_ = transform_.position_;
    oldPos_ = transform_.position_;

    if (isMoveRight_)
    {
        transform_.position_.x += speed_;
    }
    else
    {
        transform_.position_.x -= speed_;
    }

    if (transform_.position_.x >= startPos_.x + moveRange_)
    {
        isMoveRight_ = false;
    }
    else if (transform_.position_.x <= startPos_.x)
    {
        isMoveRight_ = true;
    }
}

void MovingPlatform::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void MovingPlatform::Release()
{
}

XMFLOAT3 MovingPlatform::GetPosition()
{
    return pos_;
}

XMFLOAT3 MovingPlatform::GetMoveAmount()
{
    return XMFLOAT3();
}
