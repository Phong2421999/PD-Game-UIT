#pragma once
#include "CItems.h"
#define ANI_SMALL_HEART 541
#define ANI_SMALL_HEART_ID 0
#define SMALL_HEART_WIDTH 8
#define SMALL_HEART_HEIGHT 8

#define SMALL_HEART_FLY_DISTANCE 6
#define SMALL_HEART_GRAVITY 0.0012

#define SMALL_HEART_TIME_LIVE 3000

#define SMALL_HEART_VELOCITY_X 0.025
#define SMALL_HEART_ITEM_GRAVITY 0.0001

class SmallHeart :public CItems
{
private:
	DWORD makeTime;
	float flyDistance;
	int width, height, temptX, temptY;
public:
	SmallHeart(float x, float y);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame();
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