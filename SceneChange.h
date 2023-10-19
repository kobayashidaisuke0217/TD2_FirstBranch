#pragma once
#include "Sprite.h"
#include "myMath.h"
#include <memory>
#include "textureManager.h"
#include "BlueMoon.h"
class SceneChange
{
public:
	static SceneChange* GetInstance();

	void Initialize();
	void Update();
	void Draw();

	void setmoveFlag() { moveFlag_ = true; }
	bool getchangeFlag() { return ChangeFlag_; }

private:
	Texturemanager* texturManager_;
	bool moveFlag_;
	bool ChangeFlag_;
	bool arfaUp_;
	Vector3 move_;
	std::unique_ptr<Sprite> sprite_;
	uint32_t tex;
	void Move();
	BlueMoon* blueMoon_;
	Transform saikorotransform_;
	Transform 	SpriteuvTransform;
	Vector4 material;
};