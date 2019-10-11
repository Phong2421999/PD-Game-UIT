#pragma once
#include "FrameWork/GameObject.h"

#define ANI_IDLE 560

class CLargeCandle : public CGameObject
{
private:
	int width, height;
public:
	CLargeCandle();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};