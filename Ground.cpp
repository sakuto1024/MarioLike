#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"

namespace
{
	int hModelB_;
	Transform bt;

	using std::vector;

	vector< vector<int>> mapData =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 1, 1, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
		{1, 1, 0, 1, 1, 0, 1, 0, 1, 1},
		{1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
}

Ground::Ground(GameObject* parent)
	:GameObject(parent), hModel_(-1)
{
	mapData_ = mapData;  //ファイルグローバルのmapDataをコピーして、メンバ変数mapData_に格納
}

void Ground::Initialize()
{
	hModel_ = Model::Load("uvGround.fbx");
	//Model::SetAnimFrame(hModel_, 0, 59, 1.0);

	hModelB_ = Model::Load("BlueBrick.fbx");
	
	//bt.position_.x += -18.0f;
	//.position_.z += 18.0f;

	/*transform_.position_.z += 100.0f;
	transform_.position_.y += -20.0f;
	transform_.position_.x += 30.0f;
	transform_.rotate_.x += -90.0f;*/

	
}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			if (mapData_[j][i] == 1)
			{
				bt.position_ = { -18.0f + (4.0f * j), -0.5f, 18.0f - (4.0f * i) };

				Model::SetTransform(hModelB_, bt);
				Model::Draw(hModelB_);
			}
		}	
	}
}

void Ground::Release()
{
}
