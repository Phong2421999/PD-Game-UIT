#pragma once
#include "./FrameWork/GameObject.h"
#include "FrameWork/debug.h"
#include "GameConst.h"

class CEffect : public CGameObject {
private:
	TYPE_MAKE_ITEM type;
	bool killBySimon;
	int itemId;
public:
	CEffect() {
		type = STATIC_OBJECT;
		killBySimon = false;
		itemId = 0;
	}
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	virtual bool GetLastFrame();
	virtual void reset();
	void SetKillBySimon(bool b)
	{
		this->killBySimon = b;
	}
	bool GetKillBySimon()
	{
		return killBySimon;
	}
	
	void SetMakeItem(TYPE_MAKE_ITEM type)
	{
		this->type = type;
	}
	void SetItemId(int itemId)
	{
		this->itemId = itemId;
	}
	int GetItemId()
	{
		return this->itemId;
	}
	TYPE_MAKE_ITEM GetMakeItem() {
		return type;
	}
};

typedef CEffect* LPEFT;