#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
class FollowCamera {
public:
	void Initialize();

	void Update();
	void SetTarget(const WorldTransform* target);
	const ViewProjection& GetViewProjection() { return viewprojection_; }
	bool SetShake(bool const shake);
private:
	ViewProjection viewprojection_;
	const WorldTransform* target_ = nullptr;
	Input* input_ = nullptr;

	Vector3 random{};
	int randomRange = 2;
	float ofset;
	bool shake_ = false;
private:
	void Move();
	void Rotate();
};
