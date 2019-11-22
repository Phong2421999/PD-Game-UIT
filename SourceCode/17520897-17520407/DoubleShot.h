#pragma once
#include "CItems.h"
#define ANI_DOUBLE_SHOT 557
#define ANI_DOUBLE_SHOT_ID 0

#define DOUBLE_SHOT_WIDTH 16
#define DOUBLE_SHOT_HEIGHT 12

#define DOUBLE_SHOT_TIME_LIVE 2000

#define DOUBLE_SHOT_GRAVITY 0.0005

class DoubleShot :public CItems
{
private:
	int width, height, ani;
	DWORD makeTime;
public:
	DoubleShot(float x, float y);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

};