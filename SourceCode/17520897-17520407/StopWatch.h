#pragma once
#include "CItems.h"
#define ANI_STOP_WATCH 548
#define ANI_STOP_WATCH_ID 0

#define STOP_WATCH_WIDTH 15
#define STOP_WATCH_HEIGHT 16

#define STOP_WATCH_TIME_LIVE 2000

class StopWatch : public CItems
{
private:
	int width, height;
	DWORD makeTime;
public:
	StopWatch(float x, float y);
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
