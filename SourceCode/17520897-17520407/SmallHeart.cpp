#include "SmallHeart.h"


SmallHeart::SmallHeart() {
	this->AddAnimation(ANI_SMALL_HEART);
	makeTime = GetTickCount();
	health = 1;
	type = SMALL_HEART;
}

void SmallHeart::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox(x,y);
}

void SmallHeart::RenderCurrentFrame(float x, float y, int alpha) {
	animations[0]->RenderCurrentFrame(x, y, alpha);
}

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItems::Update(dt, coObjects);
	DWORD now = GetTickCount();
	if (now - makeTime > SMALL_HEART_TIME_LIVE)
	{
		health = 0;
	}
}

void SmallHeart::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}