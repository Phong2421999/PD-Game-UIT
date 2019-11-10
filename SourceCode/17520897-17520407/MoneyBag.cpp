#pragma once
#include "MoneyBag.h"


MoneyBag::MoneyBag(float x, float y) {
	this->AddAnimation(ANI_RED_MONEY_BAG);
	this->AddAnimation(ANI_PURPLE_MONEY_BAG);
	this->AddAnimation(ANI_WHITE_MONEY_BAG);
	this->AddAnimation(1546);
	this->width = MONEY_BAG_WIDTH;
	this->height = MONEY_BAG_HEIGHT;
	this->x = x;
	this->y = y;
	int random = rand() % 3;
	switch (random)
	{
	case 0:
		ani = ANI_RED_MONEY_BAG_ID;
		type = RED_MONEY_BAG;
		break;
	case 1:
		ani = ANI_PURPLE_MONEY_BAG_ID;
		type = PURPLE_MONEY_BAG;
		break;
	case 2:
		ani = ANI_WHITE_MONEY_BAG_ID;
		type = WHITE_MONEY_BAG;
		break;
	}
	makeTime = GetTickCount();
}

void MoneyBag::Render() {
	animations[ani]->Render(x, y);
	RenderBoundingBox(x, y);
}

void MoneyBag::RenderCurrentFrame() {
	animations[ani]->RenderCurrentFrame(x, y);
}

void MoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	vy += MONEY_BAG_GRAVITY * dt;
	CItems::Update(dt, coObjects);
	//DWORD now = GetTickCount();
	//if (now - makeTime > MONEY_BAG_TIME_LIVE)
	//{
	//	health = 0;
	//}

	if (coObjects->size() >= 0)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (IsTouchSimon(coObjects->at(i)))
			{
				if (dynamic_cast<CSimon*> (coObjects->at(i)))
				{
					ani = 3;
					if (animations[ani]->getLastFrame())
					{
						DebugOut(L"\abc");
						health = 0;
					}
				}
			}
		}
	}

}

void MoneyBag::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}