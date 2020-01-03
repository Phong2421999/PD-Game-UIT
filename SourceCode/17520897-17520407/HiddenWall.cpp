#pragma once
#include "HiddenWall.h"

CHiddenWall::CHiddenWall(float x, float y, int type, int itemId) {
	this->AddAnimation(ANI_WALL);
	this->AddAnimation(ANI_WALL_BREAK);
	this->AddAnimation(ANI_GROUND);
	this->AddAnimation(ANI_FINAL_WALL);
	this->SetPosition(x, y);
	this->type = type;
	this->itemId = itemId;
	touchWhip = false;
	if (type == 0)
		ani = 0;
	else if (type == 1)
		ani = 1;
	else if (type == 2)
		ani = 2;
	else
		ani = 3;
}


void CHiddenWall::Render() {
	if (type == 0)
		ani = 0;
	else if (type == 1)
		ani = 1;
	else if (type == 2)
		ani = 2;
	else
		ani = 3;
	animations[ani]->Render(x, y);
	RenderBoundingBox(x, y);
}

void CHiddenWall::RenderCurrentFrame()
{
	animations[ani]->RenderCurrentFrame(x, y);
	RenderBoundingBox(x, y);
}


void CHiddenWall::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if ((dynamic_cast<CGround*>(coObjects->at(i))
			|| dynamic_cast<CWall*>(coObjects->at(i))))
		{
			if (this->checkAABBTouch(coObjects->at(i)))
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