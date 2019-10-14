#pragma once
#include "CStaticObject.h"
#include "CHit.h"
#include "FrameWork/debug.h"

#define ANI_IDLE 560

class CLargeCandle : public CStaticObject
{

public:
	CLargeCandle();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderCurrentFrame();
	void SetWidthHeight(float width, float height) {
		this->width = width;
		this->height = height;
	}
	void Render();
	
};