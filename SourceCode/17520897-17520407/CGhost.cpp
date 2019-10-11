#include "CGhost.h"

CGhost::CGhost() {
	this->AddAnimation(ANI_GHOST);
}

void CGhost::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox();
}

void CGhost::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}