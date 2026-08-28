#include "ClearScene.h"
#include "Engine/Text.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

ClearScene::ClearScene(GameObject* parent)
	:GameObject(parent, "ClearScene")
{
}

void ClearScene::Initialize()
{
	text_ = new Text;
	text_->Initialize();
}

void ClearScene::Update()
{
	static float timer = 0.0f;
	timer++;

	if (timer > 300.0f)
	{
		SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void ClearScene::Draw()
{
	std::string clearText;
	clearText = "CLEAR";
	text_->Draw(600, 350, clearText.c_str());
}

void ClearScene::Release()
{
}
