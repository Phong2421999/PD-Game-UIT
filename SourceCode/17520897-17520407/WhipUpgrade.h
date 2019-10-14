#pragma once
#include "CItems.h"
#define ANI_WHIP_UPGRADE 540
#define WHIP_UPGRADE_TIME_LIVE 2000

class WhipUpgrade :public CItems
{
private:
	int width, height;
	DWORD makeTime;
public:
	WhipUpgrade();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};