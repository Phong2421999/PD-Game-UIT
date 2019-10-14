#pragma once
#include "CItems.h"
#define ANI_DANGER 543

class Danger :public CItems
{
private:
	int width, height;
public:
	Danger();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};