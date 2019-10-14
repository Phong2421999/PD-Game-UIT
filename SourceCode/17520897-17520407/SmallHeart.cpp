#include "SmallHeart.h"


SmallHeart::SmallHeart() {
	this->AddAnimation(ANI_SMALL_HEART);
	type = SMALL_HEART;
	vx = SMALL_HEART_VELOCITY_X;
	makeTime = GetTickCount();
}

void SmallHeart::Render() {
	animations[ANI_SMALL_HEART_ID]->Render(x, y);
	RenderBoundingBox(x,y);
}

void SmallHeart::RenderCurrentFrame() {
	animations[ANI_SMALL_HEART_ID]->RenderCurrentFrame(x, y);
}

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	x +=  vx * sin(PI / 8)*dt;
	vy += SMALL_HEART_ITEM_GRAVITY * dt;
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