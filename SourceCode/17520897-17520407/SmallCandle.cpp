#include "SmallCandle.h"

CSmallCandle::CSmallCandle() {
	this->AddAnimation(ANI_IDLE);
}


void CSmallCandle::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox(x, y);
}


void CSmallCandle::RenderCurrentFrame() {
	animations[0]->RenderCurrentFrame(x, y);
}

void CSmallCandle::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}