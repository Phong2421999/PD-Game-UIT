#pragma once
#include"Cross.h"

Cross::Cross(float x, float y)
{
	this->AddAnimation(ANI_CROSS);
	this->x = x;
	this->y = y;
	this->width = CROSS_WIDTH;
	this->height = CROSS_HEIGHT;
	type = CROSS_ITEM;
	makeTime = GetTickCount();
}


void Cross::Render() {
	animations[ANI_CROSS_ID]->Render(x, y);
	RenderBoundingBox(x, y);
}

void Cross::RenderCurrentFrame() {
	animations[ANI_CROSS_ID]->RenderCurrentFrame(x, y);
}

void Cross::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	vy += GRAVITY * dt;

	CItems::Update(dt, coObjects);

	DWORD now = GetTickCount();
	if (now - makeTime > CROSS_TIME_LIVE)
	{
		health = 0;
	}
}

void Cross::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}