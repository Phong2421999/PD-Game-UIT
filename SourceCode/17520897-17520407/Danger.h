#pragma once
#include "CItems.h"
#define ANI_DANGER 543
#define ANI_DANGER_ID 0

#define DANGER_WIDTH 17
#define DANGER_HEIGHT 12

#define DANGER_TIME_LIVE 2000

class Danger :public CItems
{
private:
	int width, height;
	DWORD makeTime;
public:
	Danger(float x, float y);
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