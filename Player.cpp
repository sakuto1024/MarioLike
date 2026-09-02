#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Engine\\Input.h"
#include "Engine\\Debug.h"
#include "Ground.h"
#include <vector>
#include "Engine/Camera.h"

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

	XMVECTOR vFront = { 0, 0, 1, 0 }; //タンクの前方向ベクトル
	const float moveSpeed = 0.1f;
	const float CAM_HEIGHT_BIAS = 2.0f;  //カメラの高さのバイアス
	const float TPSCAM_BIAS_Y = 12.0f;
	const float TPSCAM_BIAS_Z = 40.0f;
	const int INIT_CAMPOS_X = 12.0f;

	enum CAM_TYPE
	{
		FIXED_CAM,			//固定カメラ
		TPS_CAM,		//三人称視点カメラ
		TPS_CAMROT,		//三人称視点カメラ (回転)
		FPS_CAM,		//一人称視点カメラ
		CAM_TYPE_MAX

	};

	const float G = 4.0f / 60.0f; // 重力
	const float H = 64.0f * 0.1f;
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hWalkModel_(-1), hIdleModel_(-1), velocityY(0.0f) {
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

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0.0f, 1.0f, 0.0f), 2.0f);
	AddCollider(collider);

	camType_ = CAM_TYPE::TPS_CAM;
}

void Player::Update()
{
	transform_.position_.y -= velocityY;
	velocityY += G; // 1フレームの重力

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

		if (Input::IsKey(DIK_SPACE))
		{
			velocityY = -sqrtf(2 * G * H);
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

	XMFLOAT3 wPos = { -20.0f, -26.0f, 0.0f };

	int mapX = (transform_.position_.x - wPos.x) / 4;
	int mapY = (-transform_.position_.y - wPos.y) / 2;

	Debug::Log("X = ");
	Debug::Log(mapX, true);  //後ろのtrueは改行するかどうか
	Debug::Log("Y = ");
	Debug::Log(mapY, true);  //後ろのtrueは改行するかどうか

	if (gmap[mapY][mapX] == 1)
	{
		onGround_ = true;
		

		pos  = pos - SPEED * move;
		XMStoreFloat3(&transform_.position_, pos);
		
	}

	if (velocityY >= 0.0f)
	{
		if (gmap[mapY][mapX] == 1)
		{
			velocityY = 0.0f;
			transform_.position_.y = -(mapY * 2 + wPos.y);
		}
	}


	//---------------------------------------------------------------------------


	if (Input::IsKeyDown(DIK_C)) {
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;  //0,1,2...CAM_TYPE_MAX-1の順でcamType_を切り替える
	}

	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);  //ロード：読み込み
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y - 180.0f));  //Y軸回転行列を作る
	//XMVector3TransformCoordは、ベクトルを行列で変換する関数。回転行列をベクトルにかけると、回転したベクトルを得られる
	XMVECTOR vMove = XMVector3TransformCoord(vFront, mRotY);

	switch (camType_)
	{
	case FIXED_CAM:
		SetFixedCam();
		break;

	case TPS_CAM:
	{
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + TPSCAM_BIAS_Y;
		camPos.z = camPos.z - TPSCAM_BIAS_Z;

		if (transform_.position_.x < INIT_CAMPOS_X)
		{
			camPos.x = INIT_CAMPOS_X;
			Camera::SetTarget(XMFLOAT3({ INIT_CAMPOS_X, transform_.position_.y + TPSCAM_BIAS_Y, transform_.position_.z }));
		}
		else
		{
			Camera::SetTarget(XMFLOAT3({ transform_.position_.x, transform_.position_.y + TPSCAM_BIAS_Y, transform_.position_.z }));
		}

		Camera::SetPosition(camPos);
	
	}
	break;

	case TPS_CAMROT:
	{
		XMFLOAT3 camPos;  //タンクの位置をカメラの位置にする
		XMVECTOR vCAM = { 0.0f, TPSCAM_BIAS_Y, -TPSCAM_BIAS_Z, 0.0f }; //カメラの位置をタンクの位置より少し後ろにする
		vCAM = XMVector3TransformCoord(vCAM, mRotY);  //タンクの回転をカメラの位置に反映させる
		
		
		
		XMStoreFloat3(&camPos, vPos + vCAM);  //カメラの位置をタンクの位置に反映させる
		
		

		//XMFLOAT3 camPos = transform_.position_;
		//camPos.y = camPos.y - TPSCAM_BIAS_Y;
		//camPos.z = camPos.z + TPSCAM_BIAS_Z;

		//XMVECTOR cVec = XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&camPos);
		//XMVECTOR cMove = XMVector3TransformCoord(cVec, mRotY);

		//XMStoreFloat3(&camPos, vPos + cMove);  //カメラの注意点をタンクの前方にする

		Camera::SetPosition(camPos);
		Camera::SetTarget(XMFLOAT3(transform_.position_));

	}

	break;

	case FPS_CAM:
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = camPos.y + CAM_HEIGHT_BIAS;
		Camera::SetPosition(camPos);  //カメラの位置をタンクの位置にする
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget, vPos + vMove);  //カメラの注意点をタンクの前方にする
		camTarget.y = camTarget.y + CAM_HEIGHT_BIAS;
		Camera::SetTarget(camTarget);
		break;
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
	this->KillMe();
}

void Player::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 0, -40));
}
