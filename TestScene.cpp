#include "TestScene.h"
#include "Player.h"
#include "Ground.h"
#include "Engine\\Camera.h"
#include "Enemy.h"
#include <vector>

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{	
	//pWp = Instantiate<Weapon>(this);
	//Player* pPlayer = Instantiate<Player>(this);
	//Enemy* enemy = Instantiate<Enemy>(this);
	
	Ground* pGround = Instantiate<Ground>(this);

	using std::vector;
	vector<vector<int>> gmap = pGround->GetMapData();

	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (gmap[i][j] == 3)
			{
				Player* pPlayer = Instantiate<Player>(this);
				pPlayer->SetPosition(XMFLOAT3{ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });
				pPlayer->SetGround(pGround);
			}

			if (gmap[i][j] == 4)
			{
				Enemy* enemy = Instantiate<Enemy>(this);
				enemy->SetPosition(XMFLOAT3{ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });
			}
		}
	}

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
