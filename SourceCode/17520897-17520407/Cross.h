#pragma once
#include "CItems.h"
#define ANI_CROSS 553
#define ANI_CROSS_ID 0

#define CROSS_WIDTH 16
#define CROSS_HEIGHT 17

#define CROSS_TIME_LIVE 2000

class Cross : public CItems
{
private:
	int width, height;
	DWORD makeTime;
public:
	Cross(float x, float y);
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
