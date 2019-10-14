#pragma once
#include "FrameWork/GameObject.h"
#include "CTestEnemy.h"
#include "FrameWork/debug.h"
#include "CStaticObject.h"

#define OFFSET_Y_TO_HAND_SIMON 8
#define OFFSET_X_TO_HAND_LEFT_SIMON 25
#define OFFSET_X_TO_HAND_RIGHT_SIMON 31


class Weapon : public CGameObject
{
public:
	bool isJump;
	int width, height;
	float xRender, yRender;
	DWORD timeLive;
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void RenderFlipX();

	//set
	void SetWidthHeigth(int width, int heigth) {
		this->width = width;
		this->height = heigth;
	}
	void SetRenderPos(float x, float y)
	{
		this->xRender = x;
		this->yRender = y;

	}
	//get
	void GetRenderPos(float &x, float &y)
	{
		x = this->xRender;
		y = this->yRender;
	}
	
	bool isTouchOtherObject(LPGAMEOBJECT gameObject);
	virtual void SetPositionWithSimon(float x, float y, int nx);
	virtual void SetIsJump(bool b);
	virtual bool GetLastFrame()
	{
		return false;
	}
	virtual void ResetAnimation(){}
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
