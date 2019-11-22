#pragma once
#include "PotRoast.h"

PotRoast::PotRoast(float x, float y) {
	this->AddAnimation(ANI_POT_ROAST);
	ani = ANI_POT_ROAST_ID;
	this->width = POT_ROAST_WIDTH;
	this->height = POT_ROAST_HEIGHT;
	this->x = x;
	this->y = y;
	type = POT_ROAST;
	makeTime = GetTickCount();
}

void PotRoast::Render() {
	animations[ani]->Render(x, y);
	RenderBoundingBox(x, y);
}

void PotRoast::RenderCurrentFrame() {
	animations[ani]->RenderCurrentFrame(x, y);
}

void PotRoast::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	vy += POT_ROAST_GRAVITY * dt;
	CItems::Update(dt, coObjects);
	DWORD now = GetTickCount();
	if (now - makeTime > POT_ROAST_TIME_LIVE)
	{
		health = 0;
	}

}

void PotRoast::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}