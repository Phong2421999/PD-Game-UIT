#pragma once
#include "CStaticObject.h"
#include "FrameWork/debug.h"

#define ANI_IDLE 559

class CSmallCandle : public CStaticObject
{
public:
	CSmallCandle();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderCurrentFrame();
	void SetWidthHeight(float width, float height) {
		this->width = width;
		this->height = height;
	}
	void Render();

};