#pragma once
#include "CItems.h"
#define ANI_SMALL_HEART 541
#define SMALL_HEART_TIME_LIVE 2000

class SmallHeart :public CItems
{
private:
	DWORD makeTime;
	int width, height;
public:
	SmallHeart();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame(float x, float y, int alpha = 255);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};