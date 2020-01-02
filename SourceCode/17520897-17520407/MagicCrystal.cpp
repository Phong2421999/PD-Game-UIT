#pragma once
#include "MagicCrystal.h"

MagicCrystal::MagicCrystal(float x, float y) {
	this->AddAnimation(ANI_MAGIC_CRYSTAL);
	ani = ANI_MAGIC_CRYSTAL_ID;
	this->width = MAGIC_CRYSTAL_WIDTH;
	this->height = MAGIC_CRYSTAL_HEIGHT;
	this->x = x;
	this->y = y;
	type = MAGIC_CRYSTAL;
	makeTime = GetTickCount();
}

void MagicCrystal::Render() {
	animations[ani]->Render(x, y);
	RenderBoundingBox(x, y);
}

void MagicCrystal::RenderCurrentFrame() {
	animations[ani]->RenderCurrentFrame(x, y);
}

void MagicCrystal::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	vy += MAGIC_CRYSTAL_GRAVITY * dt;
	CItems::Update(dt, coObjects);
}

void MagicCrystal::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}