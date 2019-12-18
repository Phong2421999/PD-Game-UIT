#pragma once
#include "HiddenObjects.h"
#include "FrameWork/debug.h"
#include "Ground.h"
#include "Wall.h"
#include "LockSimon.h"

#define ANI_WALL_BREAK 4000
#define ANI_WALL 4001
#define ANI_GROUND 4002



class CHiddenWall : public HiddenObjects
{
private:
	int ani;
	int type;
	int itemId;
	bool touchWhip;
public:
	CHiddenWall(float x, float y, int type, int itemId);
	void setTouchWhip(bool b)
	{
		this->touchWhip = b;
	}
	bool getTouchWhip()
	{
		return touchWhip;
	}
	int getItemId()
	{
		return itemId;
	}
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	void RenderCurrentFrame();

};