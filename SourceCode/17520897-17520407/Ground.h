#pragma once
#include "FrameWork/GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CGround : public CGameObject
{
private:
	float width, height;
public:
	
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void GetWidthHeight(float &width, float &height)
	{
		width = this->width;
		height = this->height;
	}
	void SetWidthHeigth(float width, float heigth) {
		this->width = width;
		this->height = heigth;
	}
};