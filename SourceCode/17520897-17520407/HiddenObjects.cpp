#include "HiddenObjects.h"


void HiddenObjects::SetWidthHeight(float width, float height)
{
	this->width = width;
	this->height = height;
}

void HiddenObjects::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

bool HiddenObjects::isTouchOtherObject(LPGAMEOBJECT obj)
{
	float left, top, right, bottom;
	float checkLeft, checkTop, checkRight, checkBottom;
	this->GetBoundingBox(left, top, right, bottom);
	obj->GetBoundingBox(checkLeft, checkTop, checkRight, checkBottom);
	if (CGame::GetInstance()->checkAABBTouch(left, top, right, bottom, checkLeft, checkTop, checkRight, checkBottom))
	{
		return true;
	}
	return false;
}


