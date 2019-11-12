#include "LargeHeart.h"


LargeHeart::LargeHeart(float x, float y) {
	this->AddAnimation(ANI_LARGE_HEART);
	this->width = LARGE_HEART_WIDTH;
	this->height = LARGE_HEART_HEIGHT;
	this->x = x;
	this->y = y;
	makeTime = GetTickCount();
	type = LARGE_HEART;
}

void LargeHeart::Render() {
	animations[ANI_LARGE_HEART_ID]->Render(x, y);
	RenderBoundingBox(x, y);
}

void LargeHeart::RenderCurrentFame() {
	animations[ANI_LARGE_HEART_ID]->RenderCurrentFrame(x, y);
}

void LargeHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	vy += GRAVITY * dt;

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