#pragma once
#include "BlueMoon.h"
#include "Input.h"
#include "MyMath.h"
#include "triangle.h"
#include "Iscene.h"
#include "Sprite.h"
#include "Sphere.h"
#include "model.h"
#include "worldTransform.h"
#include "ViewProjection.h"
#include "CollisionManager.h"
#include "Texturemanager.h"
#include "GlobalVariables.h"
#include "SkyDome.h"
#include "player.h"
#include"FollowCamera.h"
#include "Fireworks.h"
#include "Enemy.h"
#include <Stageh.h>
#include "SceneChange.h"
#include "EfectManager.h"
using namespace std;
class GameScene:public Iscene
{
public:
	~GameScene();
	void Initialize()override;
	void Update()override;
	
	void Draw()override;
	void Finalize()override;
private:
#pragma region 基本機能
	BlueMoon* blueMoon_;
	DirectXCommon* directXCommon_;
	Sprite* sprite_;
	Texturemanager* textureManager_;
	Input* input_;
	ViewProjection viewProjection_;
	SceneChange* Change_;

	Vector3 random{};
	int randomRange = 20;

	int blendCount_;
	void Draw2D();
	void Draw3D();
	void ApplyGlobalVariables();
	void CheckAllCollision();
	void trueFireworks();
#pragma endregion
#pragma region ゲームの機能
	int count_;
	unique_ptr<SkyDome> skyDome_=nullptr;
	unique_ptr<Model> skyDomeModel_ = nullptr;
	unique_ptr<Model> playerModel_ = nullptr;
	unique_ptr<Player> player_;
	unique_ptr<FollowCamera> followCamera_;
	//unique_ptr<ground> ground_;
	unique_ptr<Stage> stage_;

	unique_ptr<CollisionManager> collisionManager_;
	
	unique_ptr<Enemy>enemy_;
	std::unique_ptr<Model> enemyHeadModel = nullptr;
	std::unique_ptr<Model> enemyBodyModel = nullptr;
	std::unique_ptr<Model> enemyL_armModel = nullptr;
	std::unique_ptr<Model> enemyR_armModel = nullptr;
	
	//ブロック
	std::unique_ptr<Model> BlockModel_ = nullptr;

	EfectManager* efectmanager_ = nullptr;

	std::unique_ptr<Model> HeartModel_ = nullptr;
	std::unique_ptr<Model> DiamondModel_ = nullptr;
	std::unique_ptr<Model> GoalModel_ = nullptr;
	std::unique_ptr<Model> HeartGoalModel_ = nullptr;
	std::unique_ptr<Model> DiamondGoalModel_ = nullptr;
	bool nextTitle_;
	uint32_t numTexture_[10];
	std::unique_ptr<Sprite> num_[2] = { nullptr };

	Transform transform1_;
	Transform transform2_;
	Transform SpriteuvTransform;
	Vector4 material;

	//花火のエフェクト
	std::unique_ptr<Model>sterModel_;
	std::unique_ptr<Model>hertModel_;
	Model* fireworksModel_;
	std::list<Fireworks*> fireworks_;
	float changeTimer_ = 10.0f;
	bool fireworksMove_ = false;
	Audio* audio_ = nullptr;
#pragma endregion
};

