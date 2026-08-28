#include "TitleScene.h"
#include "Engine/Text.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent, "TitleScene")
{
}

void TitleScene::Initialize()
{
	text_ = new Text;
	text_->Initialize();
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))//DIKはダイレクトxのコードらしい
	{
		//SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	std::string titleName;
	titleName = "PACMAN";
	text_->Draw(600, 350, titleName.c_str());
}

void TitleScene::Release()
{
}
