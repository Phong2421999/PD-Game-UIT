#pragma once
#include "CItems.h"
#define ANI_LARGE_HEART 542
#define ANI_LARGE_HEART_ID 0
#define LARGE_HEART_WIDTH 12
#define LARGE_HEART_HEIGHT 10

#define LARGE_HEART_TIME_LIVE 2000

class LargeHeart :public CItems
{
private:
	int width, height;
	bool isDeath;
	DWORD makeTime;
public:
	LargeHeart(float x, float y);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
	void SetMakeTime(DWORD time)
	{
		this->makeTime = time;
	}
};