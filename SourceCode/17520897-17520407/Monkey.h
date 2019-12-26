#pragma once
#include "CEnemies.h"
#include "Simon.h"

#define ANI_IDLE 5771
#define ANI_JUMP 577

#define ANI_IDLE_INDEX 0
#define ANI_JUMP_INDEX 1

#define JUMP_TIME_DELAY 500
#define CLAMP_TIME_DELAY 450
#define CHECK_NX_TIME_DELAY 1500

#define MONKEY_BB_WIDTH 16
#define MONKEY_BB_HEIGHT 16

#define GRAVITY 0.001f

#define JUMP_SPEED_X 0.12f
#define JUMP_SPEED_Y 0.24f;
#define WALKING_SPEED_Y 0.22f;

#define NOT_ACTIVE_SPEED_X 0.12f

#define CLAMPING_POSITION_Y 16.0f

#define OFFSET_WALKING 60
#define VX_PART_CLAMPING 3


class Monkey : public CEnemies {
private:
	float width, height;
	int ani;
	DWORD lastMoveTime;
	DWORD lastClampTime;
	DWORD lastCheckNxTime;
	DWORD spawnTime;
	bool isJump, isClamping;
	float xWallTarget, yWallTarget;
	bool isIdle;
	float timeActive;
	int numberOfCheckSide;
public:
	Monkey();
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetPosition(float x, float y);
	void GetPosition(float &x, float &y);
	void Jump();
	void Walking();
	void Clamping();
	void setTimeActive(float time)
	{
		this->timeActive = time;
	}
};