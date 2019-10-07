#pragma once
#include "FrameWork/GameObject.h"
#include "FrameWork/debug.h"

#define SIMON_WALKING_SPEED		0.07f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.4f
#define SIMON_GRAVITY			0.0028f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define RESET_SIMON_AFTER_SIT 9
#define RESET_SIMON_AFTER_JUMP 9


#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT				500
#define SIMON_STATE_ATTACK			600


#define SIMON_ANI_IDLE_LEFT 0
#define SIMON_ANI_IDLE_RIGHT 1
#define SIMON_ANI_DIE_LEFT 2
#define SIMON_ANI_DIE_RIGHT 3
#define SIMON_ANI_WALKING_LEFT 4
#define SIMON_ANI_WALKING_RIGHT 5
#define SIMON_ANI_SIT_LEFT 6
#define SIMON_ANI_SIT_RIGHT 7
#define SIMON_ANI_THROW_LEFT 8
#define SIMON_ANO_THROW_RIGHT 9
#define SIMON_ANI_NOMAL_ATTACK_STAND_LEFT 10
#define SIMON_ANI_NOMAL_ATTACK_STAND_RIGHT 11
#define SIMON_ANI_NOMAL_ATTACK_SIT_LEFT 12
#define SIMON_ANI_NOMAL_ATTACK_SIT_RIGHT 13


#define SIMON_BBOX_WIDTH 16
#define SIMON_BBOX_HEIGHT 30

#define SIMON_SIT_BBOX_WIDTH 16
#define SIMON_SIT_BBOX_HEIGHT 23


class CSimon: public CGameObject
{
private:
	bool isJump;
	bool isSit;
	bool isAttack;
public:
	CSimon()
	{
		isJump = false;
		isSit = false;
		isAttack = false;
	}
	bool isJumping() {
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

	//Xử lí BBox tránh bị chạm;s
	void ResetAfterSit();
	void ResetAfterJump();

};