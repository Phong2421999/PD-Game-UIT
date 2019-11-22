#pragma once
#include "CStaticObject.h"
#include "FrameWork/debug.h"

#define ANI_WALL 4000

class CHiddenWall : public CStaticObject
{

public:
	CHiddenWall();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void RenderCurrentFrame();
	void SetWidthHeight(float width, float height) {
		this->width = width;
		this->height = height;
	}
	void Render();

};