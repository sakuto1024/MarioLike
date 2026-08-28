#include "TestScene.h"
#include "Player.h"
#include "Ground.h"
#include "Engine\\Camera.h"
#include "Enemy.h"
#include <vector>
#include "Food.h"
#include "Engine/Text.h"
#include "Engine/Input.h"

namespace
{
	int myScore = 10;
	int mxFood = 0;
}

//コンストラクタ
TestScene::TestScene(GameObject* parent)
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

	scene_ = TITLE;

	pText_ = new Text;
	pText_->Initialize();

	//Ground* pGround = Instantiate<Ground>(this);

	//using std::vector;
	//vector<vector<int>> gmap = pGround->GetMapData();

	//for (int j = 0; j < 10; j++)
	//{
	//	for (int i = 0; i < 10; i++)
	//	{
	//		if (gmap[i][j] == 3)
	//		{
	//			Player* pPlayer = Instantiate<Player>(this);
	//			pPlayer->SetPosition(XMFLOAT3{ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });
	//			pPlayer->SetGround(pGround);
	//		}

	//		if (gmap[i][j] == 4)
	//		{
	//			Enemy* enemy = Instantiate<Enemy>(this);
	//			enemy->SetPosition(XMFLOAT3{ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });
	//			
	//		}

	//		if (gmap[i + 10][j] > 0)
	//		{
	//			
	//			Food* food = Instantiate<Food>(this);
	//			food->SetPosition({ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });
	//			

	//			if (gmap[i + 10][j] == 1)
	//			{
	//				food->SetFoodType(FoodType::FOODTYPE_NORMAL);
	//				maxFoodN_++;
	//			}

	//			else if (gmap[i + 10][j] == 2)
	//			{
	//				food->SetFoodType(FoodType::FOODTYPE_POWER);
	//				maxFoodP_++;
	//			}

	//		}

	//		
	//	}
	//}

	////Camera::SetPosition(XMFLOAT3(0.0f, 30.0f, -40.0f));
	////Camera::SetTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));

	//pText_ = new Text;
	//pText_->Initialize();

}

//更新
void TestScene::Update()
{
	switch (scene_)
	{
	case TITLE:
		TitleUpdate();
		break;

	case GAME_PLAY:
		GamePlayUpdate();
		break;

	case CLEAR:
		ClearUpdate();
		break;

	case GAME_OVER:
		GameOverUpdate();
		break;
	}
}

void TestScene::TitleUpdate()
{
	if (Input::IsKeyDown(DIK_P))
	{
		DrawStage();
		scene_ = GAME_PLAY;
	}
}

void TestScene::GamePlayUpdate()
{
	if (maxFoodN_ == 0 && maxFoodP_ == 0)
	{
		scene_ = CLEAR;
	}
}

void TestScene::ClearUpdate()
{
	static float timer = 0.0f;
	timer++;

	if (timer >= 300.0f)
	{
		ReleaseStage();
		scene_ = TITLE;
	}
}

void TestScene::GameOverUpdate()
{
}

void TestScene::DrawStage()
{
	/*Ground* pGround = Instantiate<Ground>(this);

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


		}*/


	ground_ = Instantiate<Ground>(this);

	using std::vector;
	vector<vector<int>> gmap = ground_->GetMapData();

	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (gmap[i][j] == 3)
			{
				player_ = Instantiate<Player>(this);
				player_->SetPosition(XMFLOAT3{ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });
				player_->SetGround(ground_);
			}

			if (gmap[i][j] == 4)
			{
				enemy_ = Instantiate<Enemy>(this);
				enemy_->SetPosition(XMFLOAT3{ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });
				enemy_->SetGround(ground_);
			}

			if (gmap[i + 10][j] > 0)
			{

				food_ = Instantiate<Food>(this);
				food_->SetPosition({ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });


				if (gmap[i + 10][j] == 1)
				{
					food_->SetFoodType(FoodType::FOODTYPE_NORMAL);
					maxFoodN_++;
				}

				else if (gmap[i + 10][j] == 2)
				{
					food_->SetFoodType(FoodType::FOODTYPE_POWER);
					maxFoodP_++;
				}

			}


		}
	}

	//Camera::SetPosition(XMFLOAT3(0.0f, 30.0f, -40.0f));
	//Camera::SetTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));


}

void TestScene::ReleaseStage()
{
	player_->Release();
	enemy_->Release();
	ground_->Release();
	food_->KillMe();
}

//描画
void TestScene::Draw()
{
	if (scene_ == TITLE)
	{
		std::string titleName;
		titleName = "PACMAN";
		pText_->Draw(400, 300, titleName.c_str());
	}

	if (scene_ == GAME_PLAY)
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

	if (scene_ == CLEAR)
	{
		std::string clear;
		clear = "CLEAR";

		pText_->Draw(400, 10, clear.c_str());
	}
}

//開放
void TestScene::Release()
{
	pText_->Release();  //テキストの開放
}