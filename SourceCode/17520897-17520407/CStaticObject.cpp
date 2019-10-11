#include "CStaticObject.h"

void CStaticObject::Render() {
	RenderBoundingBox();
}

void CStaticObject::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}