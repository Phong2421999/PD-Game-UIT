#pragma once
#include "FrameWork/GameObject.h"

class HiddenObjects: public CGameObject
{
protected:
	float width, height;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) = 0;
	virtual void Render() = 0;
	virtual bool isTouchOtherObject(LPGAMEOBJECT obj);
	virtual void SetWidthHeight(float width, float height);
};