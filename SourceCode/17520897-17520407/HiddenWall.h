#pragma once
#include "HiddenObjects.h"
#include "FrameWork/debug.h"
#include "Ground.h"
#include "Wall.h"

#define ANI_WALL 4000
#define ANI_GROUND 3000


class CHiddenWall : public HiddenObjects
{
private:
	int ani;
	int type;
	bool touchWhip;
public:
	CHiddenWall(float x, float y, int type);
	void setTouchWhip(bool b)
	{
		this->touchWhip = b;
	}
	bool getTouchWhip()
	{
		return touchWhip;
	}
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

};