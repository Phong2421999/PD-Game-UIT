#pragma once
#include "CItems.h"
#define ANI_WHIP_UPGRADE 540


class WhipUpgrade :public CItems
{
private:
	int width, height;
public:
	WhipUpgrade();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void Update(DWORD dt);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};