#pragma once
#include "FrameWork/GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CGround : public CGameObject
{
private:
	int width, height;
public:
	
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetWidthHeigth(int width, int heigth) {
		this->width = width;
		this->height = heigth;
	}
};