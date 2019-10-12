#include "LargeCandle.h"

CLargeCandle::CLargeCandle() {
	this->AddAnimation(ANI_IDLE);
}


void CLargeCandle::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox();
}

void CLargeCandle::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CLargeCandle::Update(DWORD dt) {
}