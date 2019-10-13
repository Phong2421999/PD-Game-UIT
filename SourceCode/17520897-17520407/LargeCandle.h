#pragma once
#include "CStaticObject.h"
#include "CHit.h"
#include "FrameWork/debug.h"

#define ANI_IDLE 560

class CLargeCandle : public CStaticObject
{
private:
	int width, height;
public:
	CLargeCandle();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void Update(DWORD dt);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};