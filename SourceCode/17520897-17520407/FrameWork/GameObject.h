#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "CAnimations.h"
#include "../GameConst.h"
#include "debug.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;
	int ny;

	int state;

	int health;

	int weaponLevel;

	bool killBySimon;

	bool makeWeapon;

	GAME_ITEM type;

	DWORD dt;

	vector<LPANIMATION> animations;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void SetHealth(int health) { this->health = health; }
	void SetKillBySimon(bool b) { this->killBySimon = b; }
	int GetHealth() { return health; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	bool GetKillBySimon() { return killBySimon; }
	int getDirection() { return nx; }
	int GetState() { return this->state; }
	virtual void RenderCurrentFrame() {
	}
	virtual GAME_ITEM GetGameItem() { return type; }
	virtual bool GetCanSpawn() { return false; }
	virtual bool GetIsBoss() { return false; }
	virtual void SetIsBoss(bool b) {}
	virtual bool GetSpawn() { return false; }
	virtual void SetSimonHasTouch(bool b) {}
	virtual bool GetSimonHasTouch() { return false; }
	virtual void SetCanSpwan(bool b) {}
	virtual void SetSpawn(bool b) {}
	virtual void SetSpawnEnemyType(int type) {}
	virtual void SetQuantitySpawnEnemy(int quantity) {}
	virtual int GetQuantitySpawnEnemy() { return 0; }
	virtual int GetSpawnEnemyType() { return -1; }
	virtual void SetMakeTime(DWORD time){}
	virtual void GetWidthHeight(float &width, float &height) { width = 0; height = 0; }
	void RenderBoundingBox(float x, float y);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	void AddAnimation(int aniId);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void Damage(int damage) {
		health -= damage;
	}


	bool checkAABBTouch(LPGAMEOBJECT gameObject);

	~CGameObject();
};

