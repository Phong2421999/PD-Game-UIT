#include "LargeHeart.h"


LargeHeart::LargeHeart() {
	this->AddAnimation(ANI_LARGE_HEART);
	makeTime = GetTickCount();
	health = 1;
	type = LARGE_HEART;
}

void LargeHeart::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox(x, y);
}

void LargeHeart::RenderCurrentFame() {
	animations[0]->RenderCurrentFrame(x, y);
}

void LargeHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItems::Update(dt, coObjects);
	DWORD now = GetTickCount();
	if (now - makeTime > LARGE_HEART_TIME_LIVE)
	{
		health = 0;
	}
}

void LargeHeart::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}