#pragma once
#include "FrameWork/GameObject.h"
#include "Simon.h"
#define ITEM_GRAVITY 0.0005

class CItems : public CGameObject {
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	bool IsTouchSimon(LPGAMEOBJECT gameObjet);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
};