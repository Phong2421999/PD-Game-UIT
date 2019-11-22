#pragma once
#include "InvicibilityPotion.h"

InviPotion::InviPotion(float x, float y) {
	this->AddAnimation(ANI_INVI_POTION);
	ani = ANI_INVI_POTION_ID;
	this->width = INVI_POTION_WIDTH;
	this->height = INVI_POTION_HEIGHT;
	this->x = x;
	this->y = y;
	type = INVI_POTION;
	makeTime = GetTickCount();
}

void InviPotion::Render() {
	animations[ani]->Render(x, y);
	RenderBoundingBox(x, y);
}

void InviPotion::RenderCurrentFrame() {
	animations[ani]->RenderCurrentFrame(x, y);
}

void InviPotion::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	vy += INVI_POTION_GRAVITY * dt;
	CItems::Update(dt, coObjects);
	DWORD now = GetTickCount();
	if (now - makeTime > INVI_POTION_TIME_LIVE)
	{
		health = 0;
	}
}

void InviPotion::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}