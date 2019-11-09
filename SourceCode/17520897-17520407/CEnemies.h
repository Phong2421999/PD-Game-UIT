#pragma once
#include "FrameWork/GameObject.h"
#include "FrameWork/debug.h"
#define GRAVITY 0.0002

class CEnemies : public CGameObject {
protected:
	bool isActive;
public:
	CEnemies()
	{
		isActive = false;
	}
	virtual void Render() = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) = 0;
	virtual void RenderCurrentFrame() {}
	virtual void SetPosition(float x, float y) = 0;
	virtual void GetPosition(float &x, float &y) = 0;
	virtual void SetActive(bool b)
	{
		this->isActive = b;
	}
	virtual bool GetActive()
	{
		return this->isActive;
	}
};

typedef CEnemies* LPENEMIES;