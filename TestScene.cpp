#include "TestScene.h"
#include "Player.h"
#include "Ground.h"
#include "Engine\\Camera.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{	
	//pWp = Instantiate<Weapon>(this);
	Player* pPlayer = Instantiate<Player>(this);
	Ground* pGround = Instantiate<Ground>(this);
	pPlayer->SetGround(pGround);

	Camera::SetPosition(XMFLOAT3(0.0f, 30.0f, -40.0f));
	Camera::SetTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
