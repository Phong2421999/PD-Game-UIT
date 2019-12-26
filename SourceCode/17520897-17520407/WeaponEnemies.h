#pragma once
#include "FrameWork/GameObject.h"
#include "FrameWork/debug.h"


#define OFFSET_Y_TO_HAND_SIMON 8
#define OFFSET_X_TO_HAND_LEFT_SIMON 25
#define OFFSET_X_TO_HAND_RIGHT_SIMON 31

class WeaponEnemies : public CGameObject
{
protected:
	int width, height;
	DWORD timeLive;
public:
	WeaponEnemies()
	{
		width = height = 0;
	}
	virtual void Render() = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	//set
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


