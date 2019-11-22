#pragma once
#include "DoubleShot.h"

DoubleShot::DoubleShot(float x, float y) {
	this->AddAnimation(ANI_DOUBLE_SHOT);
	ani = ANI_DOUBLE_SHOT_ID;
	this->width = DOUBLE_SHOT_WIDTH;
	this->height = DOUBLE_SHOT_HEIGHT;
	this->x = x;
	this->y = y;
	type = DOUBLE_SHOT;
	makeTime = GetTickCount();
}

void DoubleShot::Render() {
	animations[ani]->Render(x, y);
	RenderBoundingBox(x, y);
}

void DoubleShot::RenderCurrentFrame() {
	animations[ani]->RenderCurrentFrame(x, y);
}

void DoubleShot::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	vy += DOUBLE_SHOT_GRAVITY * dt;
	CItems::Update(dt, coObjects);
	DWORD now = GetTickCount();
	if (now - makeTime > DOUBLE_SHOT_TIME_LIVE)
	{
		health = 0;
	}

}

void DoubleShot::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}