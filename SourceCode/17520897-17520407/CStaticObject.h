#pragma once
#include "FrameWork/GameObject.h"
class CStaticObject :public CGameObject {
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

typedef CStaticObject * LPSTO;