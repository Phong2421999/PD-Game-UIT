#pragma once
#include "CItems.h"
#define ANI_WHIP_UPGRADE 540
#define ANI_WHIP_ID 0
#define WHIP_UPGRADE_WIDTH 17
#define WHIP_UPGRADE_HEIGHT 17
#define WHIP_UPGRADE_TIME_LIVE 2000

#define WHIP_UPGRADE_GRAVITY 0.0005

class WhipUpgrade :public CItems
{
private:
	int width, height;
	DWORD makeTime;
public:
	WhipUpgrade(float x, float y);
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