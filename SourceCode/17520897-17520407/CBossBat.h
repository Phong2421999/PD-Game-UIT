#pragma once
#include "CEnemies.h"
#include "WeaponProjectile.h"
#define ANI_BOSS_BAT_IDLE 3000
#define ANI_BOSS_BAT_FLY 3001

#define ANI_ID_BOSS_BAT_IDLE 0
#define ANI_ID_BOSS_BAT_FLY 1

#define BOSS_BAT_ACTIVE_TIME 2000
#define BOSS_BAT_ACTIVE_DISTANCE 84

#define BOSS_BAT_FLY_DISTANCE_Y 8

#define BOSS_BAT_VELOCITY_X 0.07
#define BOSS_BAT_VELOCITY_Y 0.07

#define BOSS_BAT_WIDTH 48
#define BOSS_BAT_HEIGHT 22

#define BOSS_BAT_BOUNDARY_START_STAIGHT_LEFT 462
#define BOSS_BAT_BOUNDARY_START_STAIGHT_RIGHT 762

#define BOSS_FLY_START_1 1
#define BOSS_FLY_START_2 2
#define BOSS_FLY_CURVE 3
#define BOSS_FLY_STRAIGHT_1 4 // xử lí di chuyển thẳng lần 1
#define BOSS_FLY_STRAIGHT_2 5 // xử lí di chuyển thẳng lần 2
#define BOSS_ATTACK 6 // xử lí di chuyển của boss khi tấn công

#define BOUNDER_OFFSET 300

#define BOSS_BAT_MAX_FLY_Y 200
#define BOSS_BAT_MIN_FLY_Y 100

class CBossBat :public CEnemies
{
private:
	int width, height;
	int ani;

	float sx, sy; // vị trí simon theo dt

	int status; // trạng thái xử lí 

	bool isBossAttack; // trạng thái tấn công
	bool isBossActive; // kích hoạt boss

	// Vị trí cũ của Boss
	float xBefore;
	float yBefore;

	// Vị trí tiếp theo của Boss
	float xTarget;
	float yTarget;

	/*BezierCurves*/
	bool isUsingCurve; // sử dụng curve

	float x1;
	float y1;

	float x2;
	float y2;

	float x3;
	float y3;

	// Lưu lại y theo dt;
	float yLastFrame;

	DWORD startSpawnTime; // thời gian bắt đầu spawn Boss
	DWORD TimeAttacked; // thời gian bắt đầu spawn Boss
	DWORD TimeWaited; // thời gian đã chờ
	bool isWaiting;
	WeaponProjectile *weapon;

	float bounderLeft, bounderRight;
public:
	CBossBat();
	void Render();
	void RenderCurrentFrame();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	bool IsTouchSimon(LPGAMEOBJECT gameObject);


	float Curve(float n1, float n2);
	int RandomNumber(int a, int b);

	void Start();
	void StartCurves();
	void StartStaight();
	void StartAttack();
	void SetIsBoss(bool b)
	{
		isBoss = b;
	}

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

	bool GetIsBoss()
	{
		return isBoss;
	}

	void SetTargetPosition(float x, float y)
	{
		xTarget = x;
		yTarget = y;
	}
};
