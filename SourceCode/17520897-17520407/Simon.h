#pragma once
#include "FrameWork/GameObject.h"
#include "FrameWork/debug.h"

#include "SimonConst.h"


class CSimon: public CGameObject
{
private:
	bool isJump;
	bool isSit;
	bool isAttack;
	int weaponLevel;
public:
	CSimon()
	{
		isJump = false;
		isSit = false;
		isAttack = false;
		weaponLevel = SIMON_WEAPON_LEVEL_1;
	}
	bool getJump() {
		return isJump;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	//Xử lí các điều khiển của nhân vật
	void Jump();
	void Sit();
	void WalkingLeft();
	void WalkingRight();
	void Sitting();
	void Attack();

	//Xử lí khi animtion đang tấn công
	void Attacking();

	//Xử lí BBox tránh bị chạm;s
	void ResetAfterSit();
	void ResetAfterJump();

};