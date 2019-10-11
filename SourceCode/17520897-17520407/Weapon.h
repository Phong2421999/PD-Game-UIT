#pragma once
#include "FrameWork/GameObject.h"
#include "CTestEnemy.h"
#include "FrameWork/debug.h"
#include "CStaticObject.h"

#define OFFSET_Y_TO_HAND_SIMON 8
#define OFFSET_X_TO_HAND_LEFT_SIMON 25
#define OFFSET_X_TO_HAND_RIGHT_SIMON 15


class Weapon : public CGameObject
{
public:
	int width, height;
	DWORD timeLive;
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetWidthHeigth(int width, int heigth) {
		this->width = width;
		this->height = heigth;
	}
	bool isTouchOtherObject(LPGAMEOBJECT gameObject);
	virtual void SetPositionWithSimon(float x, float y, int nx);
	//set
	void SetTimeLive(DWORD timeLive)
	{
		this->timeLive = timeLive;
	}
	//get
	DWORD GetTimeLive()
	{
		return timeLive;
	}
};
