#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Engine\\Input.h"


namespace
{
	//XMVECTOR vFront = { 0, 0, -1, 0 }; //タンクの前方向ベクトル
	//const float moveSpeed = 0.1f;

	enum PLAYER_STATE
	{
		PLAYER_IDLE,
		PLAYER_WALK,
		PLAYER_TURN,  //回転中
		PLAYER_STATE_MAX  //状態の数
	};
	PLAYER_STATE pState = PLAYER_STATE::PLAYER_IDLE;

	enum PLAYER_DIRECTION
	{
		PLAYER_UP,
		PLAYER_DOWN,
		PLAYER_LEFT,
		PLAYER_RIGHT,
		PLAYER_DIRECTION_MAX  //方向の数
	};
	PLAYER_DIRECTION pDirection = PLAYER_DOWN;
	float P_ANGLE[4] = { 180.0f, 0.0f, 90.0f, 270.0f };  

	XMVECTOR P_MOVE[4] = { 
	XMVectorSet(0, 0, 1, 0),
	XMVectorSet(0, 0, -1, 0),
	XMVectorSet(-1, 0, 0, 0),
	XMVectorSet(1, 0, 0, 0)
	};

	float TURN_FRAME = 30.0f;  //回転にかかるフレーム数宇
}

Player::Player(GameObject* parent)
	:GameObject(parent), hWalkModel_(-1), hIdleModel_(-1){
	//swordDirには、初期方向として、ローカルモデルの剣の根っこから
	//先端までのベクトルとして（0,1,0)を代入しておく
	//初期位置は原点
}

void Player::Initialize()
{
	hWalkModel_ = Model::Load("Walking.fbx");
	Model::SetAnimFrame(hWalkModel_, 0, 59, 1.0);

	hIdleModel_ = Model::Load("Idle.fbx");
	Model::SetAnimFrame(hIdleModel_, 0, 839, 1.0);
}

void Player::Update()
{
	//if (Input::IsKey(DIK_A))
	//{
	//	transform_.rotate_.y -= 2.0f;
	//}
	//if (Input::IsKey(DIK_D))
	//{
	//	transform_.rotate_.y += 2.0f;
	//}


	//XMVECTOR vPos = XMLoadFloat3(&transform_.position_);  //ロード：読み込み
	//XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));  //Y軸回転行列を作る
	////XMVector3TransformCoordは、ベクトルを行列で変換する関数。回転行列をベクトルにかけると、回転したベクトルを得られる
	//XMVECTOR vMove = XMVector3TransformCoord(vFront, mRotY);

	//if (Input::IsKey(DIK_W))
	//{
	//	vPos = vPos + moveSpeed * vMove;

	//	XMStoreFloat3(&transform_.position_, vPos);  //ストア：書き込み (格納)
	//}

	//transform_.rotate_.y +=1;
	//static float angle = 0.0;
	//angle = angle + 0.3f;
	//XMMATRIX scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//XMMATRIX rotateX = XMMatrixRotationX(XMConvertToRadians(angle));
	//XMMATRIX rotate = XMMatrixRotationY(XMConvertToRadians(angle));
	//XMMATRIX translate = XMMatrixTranslation(1.0f, 0.0f, 0.0f);

	//SetWorldMatrix(scale *  rotate * translate);

	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	XMVECTOR move = XMVectorSet(0, 0, 0, 0);
	const float SPEED = 0.1;
	float angle = 0.0f;
	pState = PLAYER_STATE::PLAYER_IDLE;
	PLAYER_DIRECTION oldDir = pDirection;  
	float oldAngle = P_ANGLE[pDirection];

	if (Input::IsKey(DIK_LEFT))
	{
		//angle = 90.0f;
		pDirection = PLAYER_DIRECTION::PLAYER_LEFT;
		pState = PLAYER_STATE::PLAYER_WALK;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		//angle = -90.0f;
		pDirection = PLAYER_DIRECTION::PLAYER_RIGHT;
		pState = PLAYER_STATE::PLAYER_WALK;
	}
	if (Input::IsKey(DIK_UP))
	{
		//angle = 180.0f;
		pDirection = PLAYER_DIRECTION::PLAYER_UP;
		pState = PLAYER_STATE::PLAYER_WALK;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		//angle = 0.0f;
		pDirection = PLAYER_DIRECTION::PLAYER_DOWN;
		pState = PLAYER_STATE::PLAYER_WALK;
	}

	if (oldDir != pDirection)
	{
		pState = PLAYER_STATE::PLAYER_TURN;
	}

	//↑状態の切り替え
	//↓状態ごとの処理

	
	if (pState == PLAYER_STATE::PLAYER_TURN)
	{
		float ang = (P_ANGLE[pDirection] - oldAngle) / TURN_FRAME;

		if (P_ANGLE[pDirection] != oldAngle)
		{
			
			transform_.rotate_.y += ang;
		}
	}
	else if (pState != PLAYER_IDLE)
	{
		move = P_MOVE[pDirection];
		angle = P_ANGLE[pDirection];
		transform_.rotate_.y = angle;
	}
	
	pos = pos + SPEED * move;
	XMStoreFloat3(&transform_.position_, pos);
}

void Player::Draw()
{
	//transform_.scale_ = { 0.01,0.01,0.01 };
	//transform_.position_ = { 0, 0.0, 0 };
	if (pState == PLAYER_STATE::PLAYER_IDLE)
	{
		Model::SetTransform(hIdleModel_, transform_);
		Model::Draw(hIdleModel_);
	}

	else if (pState == PLAYER_STATE::PLAYER_WALK)
	{
		Model::SetTransform(hWalkModel_, transform_);
		Model::Draw(hWalkModel_);
	}
}


void Player::Release()
{
}
