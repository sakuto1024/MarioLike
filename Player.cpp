#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Engine\\Input.h"
#include "Engine\\Debug.h"
#include "Ground.h"
#include <vector>

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

	float turnStartAngle = 0.0f;  //回転開始時の角度を管理する変数
	float turnEndAngle = 0.0f;  //回転終了時の角度を管理する変数

	PLAYER_DIRECTION turnEndDirection = PLAYER_DOWN;  //回転終了時の向きを管理する変数

	float AdjustAngle(float angle)
	{
		if (angle > 180.0f)
		{
			angle = angle - 360.0f;
		}
		else if (angle < -180.0f)
		{
			angle = angle + 360.0f;
		}

		return angle;
	}
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

	transform_.position_ = { 1.0f, 0.0f, 2.0f };
}

void Player::Update()
{
	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	XMVECTOR move = XMVectorSet(0, 0, 0, 0);
	const float SPEED = 0.3;
	float angle = 0.0f;
	static float turnFrame = 0.0f;  //回転中のフレーム数を管理する変数
	
	if (pState != PLAYER_STATE::PLAYER_TURN) {
		pState = PLAYER_STATE::PLAYER_IDLE;
	}

	PLAYER_DIRECTION oldDir = pDirection;  //pDirection <= 今の向き
	float oldAngle = P_ANGLE[oldDir];

	if (pState != PLAYER_STATE::PLAYER_TURN)  //TURNの間は入力を受け付けない
	{
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
	}

	if (oldDir != pDirection)
	{
		pState = PLAYER_STATE::PLAYER_TURN;
		turnFrame = 0.0f;  //回転中のフレーム数をリセット
		turnStartAngle = P_ANGLE[oldDir];  //現在の方向から
		float diff = AdjustAngle(P_ANGLE[pDirection] - P_ANGLE[oldDir]);
		//diffが正の値なら、右回転、負の値なら左回転
		turnEndDirection = pDirection;//入力方向に３０フレームで回転する
		//回転終了時の角度を計算する
		turnEndAngle = turnStartAngle + diff;
	}

	Debug::Log("ROTATE = ");
	Debug::Log(transform_.rotate_.y, true);  //後ろのtrueは改行するかどうか

	//↑状態の切り替え
	//↓状態ごとの処理

	
	if (pState == PLAYER_STATE::PLAYER_TURN)
	{
		turnFrame += 1.0f;
		float t = turnFrame / TURN_FRAME;
		if (t > 1.0f)
		{
			t = 1.0f;  //1.0を超えないようにする(保険)
		}

		/*float tmpAngle = turnEndAngle - turnStartAngle;
		tmpAngle = AdjustAngle(tmpAngle);

		angle = turnStartAngle + tmpAngle * t;*/

		angle = turnStartAngle + (turnEndAngle - turnStartAngle) *t;

		transform_.rotate_.y = angle;
		if (turnFrame >= TURN_FRAME)
		{
			pDirection = turnEndDirection;
			transform_.rotate_.y = P_ANGLE[pDirection];
			pState = PLAYER_STATE::PLAYER_WALK;
		}
		return;
	}
	else if (pState != PLAYER_STATE::PLAYER_IDLE)
	{
		move = P_MOVE[pDirection];
		angle = P_ANGLE[pDirection];
		transform_.rotate_.y = angle;
	}
	
	pos = pos + SPEED * move;
	XMStoreFloat3(&transform_.position_, pos);

	using std::vector;
	vector<vector<int>> gmap = ground_->GetMapData();

	XMFLOAT3 wPos = { -20.0f, 0.0f, 20.0f };

	int mapX = (transform_.position_.x - wPos.x) / 4;
	int mapZ = (-transform_.position_.z + wPos.z) / 4;

	Debug::Log("X = ");
	Debug::Log(mapX, true);  //後ろのtrueは改行するかどうか
	Debug::Log("Z = ");
	Debug::Log(mapZ, true);  //後ろのtrueは改行するかどうか

	if (gmap[mapZ][mapX] == 1)
	{
		pos  = pos - SPEED * move;
		XMStoreFloat3(&transform_.position_, pos);
	}
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

	else if (pState == PLAYER_STATE::PLAYER_WALK || pState == PLAYER_STATE::PLAYER_TURN)
	{
		Model::SetTransform(hWalkModel_, transform_);
		Model::Draw(hWalkModel_);
	}
}


void Player::Release()
{
}
