#include "Danger.h"


Danger::Danger(float x, float y) {
	this->AddAnimation(ANI_DANGER);
	this->x = x;
	this->y = y;
	this->width = DANGER_WIDTH;
	this->height = DANGER_HEIGHT;

	makeTime = GetTickCount();
	type = DANGER_ITEM;
}

void Danger::Render() {
	animations[ANI_DANGER_ID]->Render(x, y);
	RenderBoundingBox(x,y);
}

void Danger::RenderCurrentFrame() {
	animations[ANI_DANGER_ID]->RenderCurrentFrame(x, y);
}

void Danger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	vy += DANGER_GRAVITY * dt;
	CItems::Update(dt, coObjects);
	DWORD now = GetTickCount();
	if (now - makeTime > DANGER_TIME_LIVE)
	{
		health = 0;
	}
}

void Danger::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}