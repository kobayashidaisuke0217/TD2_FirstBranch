#include "EfectManager.h"

EfectManager* EfectManager::GetInstance()
{
	static EfectManager instance;
	return &instance;
}

void EfectManager::Initialize()
{
	sterWorldtransform_.Initialize();
	hertWorldtransform_.Initialize();
	goalWorldtransform_.Initialize();
	sterModel_.reset(Model::CreateModelFromObj("Resource", "star.obj"));
	hertModel_.reset(Model::CreateModelFromObj("Resource", "heartEfect.obj"));
	panelGoal_ = false;
	panelHert_ = false;
	panelSter_ = false;
}

void EfectManager::Update()
{
	if (!panelHert_ && !panelGoal_ && !panelSter_) {
		return;
	}
	MoveSter();
	MoveHert();
	MoveGoal();
	sterWorldtransform_.UpdateMatrix();
	hertWorldtransform_.UpdateMatrix();
	goalWorldtransform_.UpdateMatrix();
}

void EfectManager::Draw(const ViewProjection& view)
{
	if (!panelHert_ && !panelGoal_ && !panelSter_) {
		return;
	}
	if (panelSter_ == true) {
		sterModel_->Draw(sterWorldtransform_, view);
	}
	if (panelHert_ == true) {
		hertModel_->Draw(hertWorldtransform_, view);
	}
	if (panelGoal_ == true) {
		goalModel_->Draw(goalWorldtransform_, view);
	}
}

void EfectManager::SelectGoal(int num)
{
	if (num == Ster) {
		goalModel_ = sterModel_.get();
	}
	if (num == Hert) {
		goalModel_ = hertModel_.get();
	}
}

void EfectManager::MoveSter()
{
	if (!panelSter_) {
		return;
	}
	sterWorldtransform_.translation_.y += 0.1f;
	sterWorldtransform_.rotation_.y += 0.1f;
	if (sterWorldtransform_.translation_.y >= 15.0f) {
		panelSter_ = false;
	}
}

void EfectManager::MoveHert()
{
	if (!panelHert_) {
		return;
	}
	hertWorldtransform_.translation_.y += 0.1f;
	hertWorldtransform_.rotation_.y += 0.1f;
	if (hertWorldtransform_.translation_.y >= 15.0f) {
		panelHert_ = false;
	}
}

void EfectManager::MoveGoal()
{
	if (!panelGoal_) {
		return;
	}
	goalWorldtransform_.translation_.y += 0.1f;
	goalWorldtransform_.rotation_.y += 0.1f;
	if (goalWorldtransform_.translation_.y >= 15.0f) {
		panelGoal_ = false;
	}
}
