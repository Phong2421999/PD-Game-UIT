#pragma once
#include "CEnemies.h"
#include "Simon.h"

#define ANI_FISH_IDLE 571
#define ANI_FISH_MOVING 572
#define ANI_FISH_ATTACK 573

#define ANI_ID_FISH_IDLE 0
#define ANI_ID_FISH_MOVING 1
#define ANI_ID_FISH_ATTACK 2

#define ANI_FISH_PROJECTILE 573

#define FISH_TIME_ACTIVE 2000

#define PROEJECTILE_TIME_LIVE 2000

#define FISH_OFFSET_FLIP_X 8

#define FISH_VELOCITY_X 0.04
#define FISH_VELOCITY_Y 0.5

#define FISH_GRAVITY 0.003

#define FISH_HEIGHT 30
#define FISH_WIDTH 16

class CUglyFish :public CEnemies
{
private:
	int width, height, ani, attackQuantity;
	float sx, sy, attackDistance;
	bool isJumpUp, isCanAttack;

	DWORD startSpawnTime, lastAttackTime, resetAttackTime;
public:
	CUglyFish(float x, float y);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	bool IsTouchSimon(LPGAMEOBJECT gameObject);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
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
};
