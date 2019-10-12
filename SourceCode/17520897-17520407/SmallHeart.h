#pragma once
#include "CItems.h"
#define ANI_SMALL_HEART 541

class SmallHeart :public CItems
{
private:
	int width, height;
public:
	SmallHeart();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};