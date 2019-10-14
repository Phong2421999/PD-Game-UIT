#include "LargeHeart.h"


LargeHeart::LargeHeart() {
	this->AddAnimation(ANI_LARGE_HEART);
	makeTime = GetTickCount();
	vx = LARGE_HEART_VELOCITY_X;
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
	x += vx * sin(PI / 8)*dt;
	vy += LARGE_HEART_ITEM_GRAVITY * dt;

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