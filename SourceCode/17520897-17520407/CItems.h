#pragma once
#include "FrameWork/GameObject.h"
#include "Simon.h"
#include "SimonConst.h"

#define PI 3.14
#define GRAVITY 0.0002

class CItems : public CGameObject {
public:
	GAME_ITEM type;

public:
	CItems()
	{
	
	}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void RenderCurrentFrame() {};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void SetMakeTime(DWORD time) {};
	bool IsTouchColision(LPGAMEOBJECT gameObjet);
};
typedef CItems * LPITEMS;