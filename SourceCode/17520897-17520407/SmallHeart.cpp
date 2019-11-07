#include "SmallHeart.h"


SmallHeart::SmallHeart() {
	this->AddAnimation(ANI_SMALL_HEART);
	type = SMALL_HEART;
	flyDistance = 0;
	vx = SMALL_HEART_VELOCITY_X;
	makeTime = GetTickCount();
	turnAround = false;
}

void SmallHeart::Render() {
	animations[ANI_SMALL_HEART_ID]->Render(x, y);
	RenderBoundingBox(x,y);
}

void SmallHeart::RenderCurrentFrame() {
	animations[ANI_SMALL_HEART_ID]->RenderCurrentFrame(x, y);
}

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItems::Update(dt, coObjects);
	vy += SMALL_HEART_ITEM_GRAVITY * dt;
	dx = vx * dt;
	DebugOut(L"\nFly: %f, dx: %f, vx: %f", flyDistance, dx, vx);
	if (flyDistance >= 0 && turnAround == false)
	{
		flyDistance += dx;
		x += dx;
	}
	if (turnAround && flyDistance <= 2.0f)
	{
		flyDistance -= dx;
		x -= dx;
	}
	if (flyDistance > 2.0f)
	{
		turnAround = true;
		flyDistance = 2.0f;
	}
	if (flyDistance < 0)
	{
		turnAround = false;
		flyDistance = 0;
	}


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