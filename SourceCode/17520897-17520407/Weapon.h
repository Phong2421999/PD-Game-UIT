#pragma once
#include "FrameWork/GameObject.h"
#include "CEnemies.h"
#include "GameConst.h"

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

	//set
	void SetTimeLive(DWORD timeLive)
	{
		this->timeLive = timeLive;
	}

	DWORD GetTimeLive()
	{
		return timeLive;
	}
};
