#pragma once
#include "CEnemies.h"
#include "Simon.h"

#define ANI_IDLE 5771
#define ANI_JUMP 577

#define ANI_IDLE_INDEX 0
#define ANI_JUMP_INDEX 1

#define JUMP_TIME_DELAY 300
#define CLAMP_TIME_DELAY 450


#define BB_WIDTH 16
#define BB_HEIGHT 16

#define GRAVITY 0.001f

#define JUMP_SPEED_X 0.12f
#define JUMP_SPEED_Y 0.28f
#define WALKING_SPEED_Y 0.26f

#define CLAMPING_POSITION_Y 16.0f

#define OFFSET_WALKING 60

class Monkey : public CEnemies {
private:
	float width, height;
	int ani;
	DWORD lastMoveTime;
	DWORD lastClampTime;
	bool isJump, isClamping;
	float xWallTarget;
	bool isIdle;
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
};