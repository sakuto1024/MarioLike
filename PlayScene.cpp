#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Food.h"
#include "Ground.h"
#include <vector>
#include "Engine/Camera.h"
#include "Engine/Text.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene"), score_(0)
{
}

void PlayScene::Initialize()
{
	pText_ = new Text;
	pText_->Initialize();

	ground_ = Instantiate<Ground>(this);

	using std::vector;
	vector<vector<int>> gmap = ground_->GetMapData();

	for (int j = 0; j < ground_->GetMapWidth(); j++)
	{
		for (int i = 0; i < ground_->GetMapHeight(); i++)
		{
			if (gmap[i][j] == 3)
			{
				player_ = Instantiate<Player>(this);
				player_->SetPosition(XMFLOAT3{ -18.0f + (4.0f * j), 20.0f - (4.0f * i), 0.0f });
				player_->SetGround(ground_);
			}

			if (gmap[i][j] == 4)
			{
				enemy_ = Instantiate<Enemy>(this);
				enemy_->SetPosition(XMFLOAT3{ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });
				enemy_->SetGround(ground_);
			}

			//if (gmap[i + 10][j] > 0)
			//{

			//	food_ = Instantiate<Food>(this);
			//	food_->SetPosition({ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });


			//	if (gmap[i + 10][j] == 1)
			//	{
			//		food_->SetFoodType(FoodType::FOODTYPE_NORMAL);
			//		maxFoodN_++;
			//	}

			//	else if (gmap[i + 10][j] == 2)
			//	{
			//		food_->SetFoodType(FoodType::FOODTYPE_POWER);
			//		maxFoodP_++;
			//	}

			//}
		}
	}
}

void PlayScene::Update()
{
	//if (maxFoodN_ == 0 && maxFoodP_ == 0)
	//{
	//	//SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//	SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
	//	pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	//}
}

void PlayScene::Draw()
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

void PlayScene::Release()
{
}

//test
