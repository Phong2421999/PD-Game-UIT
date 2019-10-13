#include "LargeHeart.h"


LargeHeart::LargeHeart() {
	this->AddAnimation(ANI_LARGE_HEART);
}

void LargeHeart::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox(x,y);
}

void LargeHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItems::Update(dt, coObjects);
}

void LargeHeart::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}