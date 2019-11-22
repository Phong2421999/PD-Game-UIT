#pragma once
#include "HiddenWall.h"

CHiddenWall::CHiddenWall(float x, float y, int type) {
	this->AddAnimation(ANI_WALL);
	this->AddAnimation(ANI_GROUND);
	this->SetPosition(x, y);
	this->type = type;
	touchWhip = false;
	if (type == 0)
		ani = 0;
	else
		ani = 1;
}


void CHiddenWall::Render() {
	animations[ani]->Render(x, y);
	RenderBoundingBox(x, y);
}


void CHiddenWall::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	touchWhip = false;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (this->checkAABBTouch(coObjects->at(i)))
		{
			if (dynamic_cast<CGround*>(coObjects->at(i)))
			{
				coObjects->at(i)->SetHealth(this->health);
			}
		}
	}
}

void CHiddenWall::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}