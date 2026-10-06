#pragma once
#include "Engine/GameObject.h"

class MovingPlatform : public GameObject
{
public:
	MovingPlatform(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetMoveAmount(); // 今フレーム何m動いたか

private:
	XMFLOAT3 startPos_;       // 開始位置
	XMFLOAT3 endPos_;         // 終了位置
	XMFLOAT3 oldPos_;         // 1フレーム前の位置
	XMFLOAT3 pos_;
	float speed_;
	float moveRange_;
	bool isMoveRight_;

	int hModel_;
};