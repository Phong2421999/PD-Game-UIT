#pragma once
#include "FrameWork/GameObject.h"
#include "Simon.h"
#include "SimonConst.h"
#define ITEM_GRAVITY 0.0005

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
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	bool IsTouchSimon(LPGAMEOBJECT gameObjet);
};
typedef CItems * LPITEMS;