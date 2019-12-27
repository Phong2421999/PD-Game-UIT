#pragma once
#include "CEnemies.h"
#include "Simon.h"
#include "Bone.h"

#define ANI_WALKING 575
#define ANI_IDLE 5751
#define ANI_ATTACK 5752

#define ANI_WALKING_INDEX 0
#define ANI_IDLE_INDEX 1
#define ANI_ATTACK_INDEX 2

#define MONKEY_BB_WIDTH 16
#define MONKEY_BB_HEIGHT 16

#define SKELETON_GRAVITY 0.002f

#define SKELETON_BB_WIDTH 16
#define SKELETON_BB_HEIGHT 32

#define SKELETON_DELAY_ATTACK_TIME 2000

#define SKELETON_WALKIN_SPEED 0.07f

#define SKELETON_MAKE_WEAPON_DELAY 350
#define SKELETON_JUMP_DELAY 1800


#define MAX_WEAPON_QUANTITY 3

#define VY_JUMP_PART 10
#define VX_JUMP_PART 10

#define WALKING_MODE 0
#define JUMP_MODE 1

class Skeleton : public CEnemies {
private:
	float width, height;
	int ani;
	DWORD spawnTime;
	DWORD lastAttackTime;
	DWORD lastMakeBoneTime;
	DWORD lastJumpTime;
	bool isWalking, isAttack, isJump, isIdle;
	float xTarget, yTarget;
	float xMiddleWalking;
	float offsetWithSimon;
	int boneQuantity;
	vector<Bone*> bones;
	int mode;
public:
	Skeleton();
	void Render();
	void RenderCurrentFrame();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetPosition(float x, float y);
	void GetPosition(float &x, float &y);
	void Jump();
	void Attack();
	void Walking();
	void SetAttack(bool b)
	{
		this->isAttack = b;
	}
	void SetOffsetWithSimon(float dis)
	{
		this->offsetWithSimon = dis;
	}
};