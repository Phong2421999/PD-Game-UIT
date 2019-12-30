#pragma once
#include "FrameWork/GameObject.h"
#include "FrameWork/debug.h"

#define GRAVITY 0.0002

#define GHOST_ID 0
#define PANTHER_ID 1
#define BAT_ID 2
#define FISH_ID 3
#define MONKEY_ID 11
#define EAGLE_ID 12
#define MONKEY_EAGLE_ID 13
#define SKELETON_ID 14
#define FINAL_BOSS_ID 999



#define BOSS_BAT_ID 100

class CEnemies : public CGameObject {
protected:
	bool isActive;
	bool isBoss;
public:
	CEnemies()
	{
		isBoss = false;
		isActive = false;
	}
	virtual void Render() = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) = 0;
	bool IsTouchColision(LPGAMEOBJECT gameObject) {
		return checkAABBTouch(gameObject);
	}
	virtual void RenderCurrentFrame() {}
	virtual void SetPosition(float x, float y) = 0;
	virtual void GetPosition(float &x, float &y) = 0;
	virtual void SetActive(bool b)
	{
		this->isActive = b;
	}
	virtual bool GetIsBoss()
	{
		return this->isBoss;
	}
	virtual bool GetActive()
	{
		return this->isActive;
	}
	~CEnemies()
	{
	}
};

typedef CEnemies* LPENEMIES;