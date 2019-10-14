#pragma once
#include "CItems.h"
#define ANI_LARGE_HEART 542
#define LARGE_HEART_TIME_LIVE 2

class LargeHeart :public CItems
{
private:
	int width, height;
	bool isDeath;
	DWORD makeTime;
public:
	LargeHeart();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};