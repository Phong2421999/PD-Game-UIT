#pragma once
#include "CItems.h"
#include "CMoneyEffect.h"
#define ANI_RED_MONEY_BAG 546
#define ANI_PURPLE_MONEY_BAG 547
#define ANI_WHITE_MONEY_BAG 647

#define ANI_RED_MONEY_BAG_ID 0
#define ANI_PURPLE_MONEY_BAG_ID 1
#define ANI_WHITE_MONEY_BAG_ID 2

#define MONEY_BAG_WIDTH 12
#define MONEY_BAG_HEIGHT 14

#define MONEY_BAG_TIME_LIVE 2000

#define MONEY_BAG_GRAVITY 0.0005

class MoneyBag :public CItems
{
private:
	int width, height, ani;
	DWORD makeTime;
public:
	MoneyBag(float x, float y);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame();
	GAME_ITEM GetGameItem() {
		return type;
	}
	void SetMakeTime(DWORD time)
	{
		this->makeTime = time;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};