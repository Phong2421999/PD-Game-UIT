#include "Danger.h"


Danger::Danger() {
	this->AddAnimation(ANI_DANGER);
}

void Danger::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox();
}

void Danger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItems::Update(dt, coObjects);
}

void Danger::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}