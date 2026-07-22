#include "TestScene.h"
#include "Player.h"
#include "Ground.h"
#include "Engine\\Camera.h"
#include "Enemy.h"
#include <vector>
#include "Food.h"
#include "Engine/Text.h"

namespace
{
	int myScore = 10;
	int mxFood = 0;
}

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"), score_(0)
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
					maxFoodN_++;
				}

				else if (gmap[i + 10][j] == 2)
				{
					food->SetFoodType(FoodType::FOODTYPE_POWER);
					maxFoodP_++;
				}

			}

			
		}
	}

	//Camera::SetPosition(XMFLOAT3(0.0f, 30.0f, -40.0f));
	//Camera::SetTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));

	pText_ = new Text;
	pText_->Initialize();
	
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
	std::string scrText;
	scrText = "SCORE:" + std::to_string(score_);
	pText_->Draw(20, 20, scrText.c_str());

	std::string fdnText;
	fdnText = "NORMAL_FOOD:" + std::to_string(maxFoodN_);
	pText_->Draw(20, 50, fdnText.c_str());

	std::string fdpText;
	fdpText = "POWER_FOOD:" + std::to_string(maxFoodP_);
	pText_->Draw(300, 50, fdpText.c_str());
}

//開放
void TestScene::Release()
{
	pText_->Release();  //テキストの開放
}
