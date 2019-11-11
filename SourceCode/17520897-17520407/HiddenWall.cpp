#pragma once
#include "HiddenWall.h"

CHiddenWall::CHiddenWall() {
	this->AddAnimation(ANI_WALL);
}


void CHiddenWall::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox(x, y);
}


void CHiddenWall::RenderCurrentFrame() {
	animations[0]->RenderCurrentFrame(x, y);
}

void CHiddenWall::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}