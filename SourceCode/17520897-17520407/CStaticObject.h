#pragma once
#include "FrameWork/GameObject.h"
class CStaticObject :public CGameObject {
public:
	float width, height;
	int itemId;
public:
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void RenderCurrentFrame() {};
	virtual void SetWidthHeigth(float width, float height) {
		this->width = width;
		this->height = height;
	}
	virtual void SetItemId(int itemId)
	{
		this->itemId = itemId;
	}
	virtual int GetItemId()
	{
		return this->itemId;
	}
};

typedef CStaticObject * LPSTO;