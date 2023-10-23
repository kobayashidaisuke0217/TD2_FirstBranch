#pragma once
#include "Model.h"
#include "Worldtransform.h"
#include <memory>
#include "ViewProjection.h"
enum SelectEfect {
	Ster,
	Hert,
};
class EfectManager
{
public:
	static EfectManager* GetInstance();
	void Initialize();
	void Update();
	void Draw(const ViewProjection& view);
	void SetPanelSter() { panelSter_ = true; }
	void SetPanelHert() { panelHert_ = true; }
	void SetPanelGoal() { panelGoal_ = true; }
	void SelectGoal(int num);
	void SetSterTransform(const Vector3& Position) { sterWorldtransform_.translation_ = Position; }
	void SetHertTransform(const Vector3& Position) { hertWorldtransform_.translation_ = Position; }
	void SetGoalTransform(const Vector3& Position) { goalWorldtransform_.translation_ = Position; }
private:
	bool panelSter_;
	bool panelHert_;
	bool panelGoal_;
	WorldTransform sterWorldtransform_;
	WorldTransform hertWorldtransform_;
	WorldTransform goalWorldtransform_;
	std::unique_ptr<Model>sterModel_;
	std::unique_ptr<Model>hertModel_;
	Model* goalModel_;
	int efectNum = 0;
private:
	void MoveSter();
	void MoveHert();
	void MoveGoal();
};

