#include "TestScene.h"
#include "Player.h"
#include "Ground.h"
#include "Engine\\Camera.h"
#include "Enemy.h"
#include <vector>
#include "Food.h"

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
	//Enemy* enemys = Instantiate<Enemy>(this);
	//enemys->SetPosition(XMFLOAT3(0.0f, 23.0f, -30.0f));
	
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

			if (gmap[i + 10][j] > 0)
			{
				
				Food* food = Instantiate<Food>(this);
				food->SetPosition({ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });


				if (gmap[i + 10][j] == 1)
				{
					food->SetFoodType(FoodType::FOODTYPE_NORMAL);
				}

				else if (gmap[i + 10][j] == 2)
				{
					food->SetFoodType(FoodType::FOODTYPE_POWER);
				}

			}

			
		}
	}

	//Camera::SetPosition(XMFLOAT3(0.0f, 30.0f, -40.0f));
	//Camera::SetTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));
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
