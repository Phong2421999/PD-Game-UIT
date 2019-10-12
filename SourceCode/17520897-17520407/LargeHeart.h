#pragma once
#include "CItems.h"
#define ANI_LARGE_HEART 542

class LargeHeart :public CItems
{
private:
	int width, height;
public:
	LargeHeart();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};