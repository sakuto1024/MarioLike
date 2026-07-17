#pragma once
#include "Engine/GameObject.h"



class Ground;  //前方宣言（ポインタだけでいいときは前方宣言でOK)
               //(Gound::～　とかやりたいときは前方宣言じゃダメ）

class Player : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void SetGround(Ground* ground) { ground_ = ground; }

private:
	int hWalkModel_;  //歩きモーションのモデルハンドル
	int hIdleModel_;  //待機アニメーションのモデルハンドル

	Ground* ground_;//地面オブジェクトのポインタ

	int camType_;  //カメラの種類

	void  SetFixedCam();  //固定カメラの処理




};

