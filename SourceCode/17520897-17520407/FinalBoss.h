#pragma once
#pragma once
#include "CEnemies.h"
#include "Simon.h"
#include "WeaponProjectile.h"

#define FINAL_BOSS_ANI_FACE 3002
#define FINAL_BOSS_ANI_BODY_START_ATTACK 3003
#define FINAL_BOSS_ANI_BODY_ATTACK 3004
#define FINAL_BOSS_ANI_CHAOS_IDLE 30051
#define FINAL_BOSS_ANI_CHAOS_START_ATTACK 30052
#define FINAL_BOSS_ANI_CHAOS_ATTACK 30053

#define FINAL_BOSS_ANI_FACE_INDEX 0
#define FINAL_BOSS_ANI_BODY_START_ATTACK_INDEX 1
#define FINAL_BOSS_ANI_BODY_ATTACK_INDEX 2
#define FINAL_BOSS_ANI_CHAOS_IDLE_INDEX 3
#define FINAL_BOSS_ANI_CHAOS_START_ATTACK_INDEX 4
#define FINAL_BOSS_ANI_CHAOS_ATTACK_INDEX 5

#define FINAL_BOSS_NOMAL_MODE 0
#define FINAL_BOSS_CHAOS_MODE 1

#define FINAL_BOSS_MAX_HEATH 16

#define OFFSET_FOR_BODY_X 8
#define OFFSET_FOR_BODY_FLIP_X 12

#define FLIP_OFFSET_FOR_BODY 13
#define FLIP_OFFSET_FOR_HEAD 4
#define FLIP_OFFSET_FOR_CHAOS 25

#define FACE_START_VY 0.07f

#define FINAL_BOSS_STATE_START 0
#define FINAL_BOSS_STATE_START_ATTACK 1
#define FINAL_BOSS_STATE_ATTACK 2
#define FINAL_BOSS_STATE_INVISIABLE 3

#define CHAOS_BOSS_STATE_IDLE 0
#define CHAOS_BOSS_STATE_START_ATTACK 1
#define CHAOS_BOSS_STATE_ATTACK 2

#define FINAL_BOSS_NOMAL_BB_WIDTH 8
#define FINAL_BOSS_NOMAL_BB_HEIGHT 14

#define CHAOS_BOSS_BB_WIDTH 50
#define CHAOS_BOSS_BB_HEIGHT 82

#define PULL_UP_CHAOS_BOSS 30

#define TAKE_DAMAGE_COUNT 2

#define CHAOS_BOSS_OFFSET_MAX_X 255

#define CHAOS_BOSS_START_ATTACK_DELAY 1300

#define FINAL_BOSS_ATTACK_DELAY 800;

#define FINAL_BOSS_MAX_START_ATTACK_OFFSET 96
#define FINAL_BOSS_MIN_START_ATTACK_OFFSET 48

#define TIME_TO_TOUCH_SIMON_VX 60

#define CHAOS_BOSS_HIGHT_JUMP_VY 0.28f
#define CHAOS_BOSS_SHORT_JUMP_VY 0.21f
#define CHAOS_BOSS_GRAVITY 0.0005f

#define CHAO_BOSS_SHOT_SIMON_DISTANCE 140

#define FINAL_BOSS_WEAPON_QUANTITY 3

#define FINAL_BOSS_WEAPON_VX 0.09f
#define FINAL_BOSS_WEAPON_VY 0.12f

#define FINAL_BOSS_WEAPON_VX_PLUS 0.001f
#define FINAL_BOSS_WEAPON_VY_PLUS 0.001f
#define CHAOS_BOSS_TOP_WEAPON_VY_PLUS 0.001f
#define CHAOS_BOSS_MIDDLE_WEAPON_VY_PLUS 0.0014f
#define CHAOS_BOSS_BOTTOM_WEAPON_VY_PLUS 0.0018

#define FINAL_BOSS_MIDDLE_WEAPON_INDEX 0
#define FINAL_BOSS_BOTTOM_WEAPON_INDEX 1
#define FINAL_BOSS_TOP_WEAPON_INDEX 2


#define WEAPON_OFFSET_Y_DEFAULT 28

#define FINAL_BOSS_INVISIABLE_DELAY 2000
#define FINAL_BOSS_START_ATTACK_DELAY 800
#define FINAL_BOSS_ATTACK_DELAY 1000
#define CHAOS_BOSS_SHOT_DELAY 800

#define FINAL_BOSS_WEAPON_OFFSET_X 8
#define FINAL_BOSS_WEAPON_OFFSET_Y 25

#define CHAOS_BOSS_LOCK_TIME 300

class FinalBoss :public CEnemies
{
private:
	int width, height, ani, bodyAni;
	bool isStartAttack, isAttack;
	DWORD lastTimeAttack;
	DWORD lastTimeInvisiable;
	DWORD lastLockTime;
	DWORD makeTime;
	bool isBoss;
	bool isActive;
	int mode;
	bool isHasBody;
	bool isHasFace;
	bool isHurt;
	bool isInvisiable;
	bool isFirstAttack;
	float xTarget, yTarget;
	int damageCount;
	bool isLock;
	bool isHightJump;
	bool isShot;
	bool isJump;
	vector<WeaponProjectile*>weapons;
public:
	FinalBoss();
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Damage(int damage);
	void SetPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void GetPosition(float &x, float &y)
	{
		x = this->x;
		y = this->y;
	}
	void SetIsBoss(bool b)
	{
		this->isBoss = b;
	}
	bool GetIsBoss()
	{
		return isBoss;
	}
	void SetTargetPosition(float x, float y)
	{
		this->xTarget = x;
		this->yTarget = y;
	}
	void SetLock(bool b)
	{
		lastLockTime = GetTickCount();
		this->isLock = b;
	}
	void MakeWeapon();
};
