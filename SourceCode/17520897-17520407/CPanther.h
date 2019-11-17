#pragma once
#include "CEnemies.h"
#include "Simon.h"
#include "Ground.h"
#define ANI_PANTHER_IDLE 566
#define ANI_PANTHER_RUN 567
#define ANI_PANTHER_JUMP 568

#define ANI_ID_PANTHER_IDLE 0
#define ANI_ID_PANTHER_RUN 1
#define ANI_ID_PANTHER_JUMP 2

#define PANTHER_OFFSET_FLIP_X 12

#define PANTHER_WIDTH 30
#define PANTHER_HEIGHT 16
#define PANTHER_GRAVITY 0.0002
#define PANTHER_VELOCITY_X 0.1



class CPanther :public CEnemies {
private:
	int width, height;
	int ani;

	bool isAttack;
	bool isJump;
	
	float yBefore;

	float attackDistance; // tính khoảng cách để tấn công
	float sx, sy; // lấy vị trí simon
public:
	CPanther(float x, float y);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Run();
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