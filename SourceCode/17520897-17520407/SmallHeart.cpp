#include "SmallHeart.h"


SmallHeart::SmallHeart(float x, float y) {
	this->AddAnimation(ANI_SMALL_HEART);
	this->width = SMALL_HEART_WIDTH;
	this->height = SMALL_HEART_HEIGHT;
	this->x = x;
	this->y = y;
	this->temptX = x;
	this->temptY = y;
	vx = SMALL_HEART_VELOCITY_X;
	vy = 0;
	type = SMALL_HEART;
	flyDistance = 0;
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
	vy = SMALL_HEART_GRAVITY * dt;
	CItems::Update(dt, coObjects);

	if (x > temptX + SMALL_HEART_FLY_DISTANCE)
	{
		vx = -SMALL_HEART_VELOCITY_X;
	}
	if (x < temptX - SMALL_HEART_FLY_DISTANCE)
	{
		vx = SMALL_HEART_VELOCITY_X;
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