#include "Danger.h"


Danger::Danger() {
	this->AddAnimation(ANI_DANGER);
}

void Danger::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox(x,y);
}

void Danger::RenderCurrentFrame() {
	animations[0]->RenderCurrentFrame(x, y);
}

void Danger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	dx = vx * dt;
	x += dx;
}

void Danger::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}