#pragma once
#include "Simon.h"
#include "CStaticObject.h"
class ChangeSceneObjects : public CStaticObject {
private:
	int sceneId;
	CSimon* simon;
public:
	ChangeSceneObjects()
	{
		simon = CSimon::getInstance();
	}
	void SetWidthHeight(float width, float height)
	{
		this->width = width;
		this->height = height;
	}
	void SetSceneId(int sceneId)
	{
		this->sceneId = sceneId;
	}
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom)
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};