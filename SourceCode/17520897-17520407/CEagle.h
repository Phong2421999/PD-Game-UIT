#pragma once
#include "CEnemies.h"

#define ANI_FLY 578
#define ANI_IDLE 5781

#define ANI_IDLE_INDEX 0
#define ANI_FLY_INDEX 1

#define FLY_SPEED 0.12f

#define EAGLE_BB_WIDTH 32
#define EAGLE_BB_HEIGHT 32

#define IN_AIR_TIME 250

#define MAX_Y_SPAWN 100
#define MIN_Y_SPAWN 90

class CEagle : public CEnemies
{
private:
	int ani;
	float width, height;
	DWORD lastInAirTime;
	DWORD lastIdleTime;
	float idleTime;
	float inAirTime;
	bool isIdle;
	bool isFly;
public:
	CEagle();
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void RenderCurrentFrame();
	void SetPosition(float x, float y);
	void GetPosition(float &x, float &y);
	void setIdleTime(float time)
	{
		this->idleTime = time;
	}
};