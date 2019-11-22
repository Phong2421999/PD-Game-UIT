#pragma once
#include "CItems.h"
#define ANI_POT_ROAST 555
#define ANI_POT_ROAST_ID 0

#define POT_ROAST_WIDTH 16
#define POT_ROAST_HEIGHT 12

#define POT_ROAST_TIME_LIVE 2000

#define POT_ROAST_GRAVITY 0.0005

class PotRoast :public CItems
{
private:
	int width, height, ani;
	DWORD makeTime;
public:
	PotRoast(float x, float y);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	
};