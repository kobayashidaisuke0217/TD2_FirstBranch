#include "Stageh.h"


void Stage::Initialize(Model* models) {
		modelNormal_=models;
	for (int i = 0; i < 25; i++) {
	
		worldTransformNormal_[i].Initialize();
	}
	
	
}

void Stage::Update() {
	for (int i = 0; i < 25; i++) {
		worldTransformNormal_[i].UpdateMatrix();
	}
	

}

void Stage::Draw(const ViewProjection& viewprojection) {

	for (int i = 0; i < 25; i++) {
		modelNormal_->Draw(worldTransformNormal_[i], viewprojection);
	}
	

}


