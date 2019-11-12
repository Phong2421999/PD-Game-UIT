#include "CheckStair.h"

void CheckStair::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CheckStair::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	for (int i = 0; i < coObjects->size(); i++)
	{
		CSimon* simon = CSimon::getInstance();
		if (this->isTouchOtherObject(simon))
		{
			simon->setCanOnStair(true);
			simon->setStairType(type);
			simon->nx = this->nx;
		}
	}
}

void CheckStair::Render()
{
	this->RenderBoundingBox(x, y);
}