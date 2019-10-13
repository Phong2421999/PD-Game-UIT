#include "SmallHeart.h"


SmallHeart::SmallHeart() {
	this->AddAnimation(ANI_SMALL_HEART);
}

void SmallHeart::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox(x,y);
}

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItems::Update(dt, coObjects);
}

void SmallHeart::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}