#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Engine/CsvReader.h"
#include "Food.h"

namespace
{
	int hModelB_;
	int hModelF_;
	int hModelFP_;
	Transform bt;
	Transform ft;
	Transform fpt;

	using std::vector;

	/*vector< vector<int>> mapData =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
		{1, 1, 0, 1, 1, 0, 0, 0, 0, 1},
		{1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
		{1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};*/
}

Ground::Ground(GameObject* parent)
	:GameObject(parent), hModel_(-1), mapWidth_(-1), mapHeight_(-1)
{
	CsvReader csvData;
	csvData.Load("map.csv");  //csvファイルを読み込む
	mapWidth_ = csvData.GetWidth();  //列数を取得
	mapHeight_ = csvData.GetHeight();  //行数を取得

	//mapData_を初期化 mapHeight_個のvector<int>の配列を作る
	mapData_ = vector<vector<int>>(mapHeight_, vector<int>(mapWidth_, 0));  //ファイルグローバルのmapDataをコピーして、メンバ変数mapData_に格納
	objMap_ = vector<vector<int>>(mapHeight_, vector<int>(mapWidth_, 0));


	for (int x = 0; x < mapWidth_; x++)
	{
		for (int y = 0; y < mapHeight_; y++)
		{
			mapData_[y][x] = csvData.GetValue(x, y);
		}
	}

	for (int x = 0; x < mapWidth_; x++)
	{
		for (int y = 0; y < mapHeight_; y++)
		{
			objMap_[y][x] = csvData.GetValue(x, y + 10); //CSVの値をobjMap_に格納
		}
	}


	fpt.scale_.x *= 2.0f;
	fpt.scale_.y *= 2.0f;
	fpt.scale_.z *= 2.0f;
}

void Ground::Initialize()
{
	hModel_ = Model::Load("uvGround.fbx");
	//Model::SetAnimFrame(hModel_, 0, 59, 1.0);

	hModelB_ = Model::Load("BlueBrick.fbx");

	hModelF_ = Model::Load("Feed.fbx");

	hModelFP_ = Model::Load("FeedP.fbx");

	//bt.position_.x += -18.0f;
	//.position_.z += 18.0f;

	/*transform_.position_.z += 100.0f;
	transform_.position_.y += -20.0f;
	transform_.position_.x += 30.0f;
	transform_.rotate_.x += -90.0f;*/


}

void Ground::Update()
{
	fpt.rotate_.y += 3.0f;
}

void Ground::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (mapData_[i][j] == 1)
			{
				bt.position_ = { -18.0f + (4.0f * j), -2.0f, 18.0f - (4.0f * i) };

				Model::SetTransform(hModelB_, bt);
				Model::Draw(hModelB_);
			}
		}
	}


	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			/*if (mapData_[i + 10][j] > 0)
			{

				Food* food = Instantiate<Food>(this);
				food->SetPosition({ -18.0f + (4.0f * j), 0.0f, 18.0f - (4.0f * i) });


				if (mapData_[i + 10][j] == 1)
				{
					food->SetFoodType(FoodType::FOODTYPE_NORMAL);
				}

				else if (mapData_[i + 10][j] == 2)
				{
					food->SetFoodType(FoodType::FOODTYPE_POWER);
				}

			}*/
		}
	}
}

void Ground::Release()
{
	this->KillMe();
}