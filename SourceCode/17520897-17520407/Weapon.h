#pragma once
#include "FrameWork/GameObject.h"
#include "CTestEnemy.h"
#include "GameConst.h"
#include "FrameWork/debug.h"


class Weapon : public CGameObject
{
private:
	int width, height;
	DWORD timeLive;
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetWidthHeigth(int width, int heigth) {
		this->width = width;
		this->height = heigth;
	}
	bool isTouchOtherObject(LPGAMEOBJECT gameObject);
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
