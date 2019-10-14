#pragma once
#include "./FrameWork/GameObject.h"

class CEnemies : public CGameObject {
private:
	int width, height;
public:

	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void RenderCurrentFrame(float x, float y, int alpha) = 0;
	virtual void SetWidthHeigth(int width, int heigth) {
		this->width = width;
		this->height = heigth;
	}
	virtual void Damage();
};