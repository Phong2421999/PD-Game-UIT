#pragma once
#include "./FrameWork/GameObject.h"
#include "FrameWork/debug.h"
#include "GameConst.h"

class CEffect : public CGameObject {
private:
	TYPE_MAKE_ITEM type;
	bool killBySimon;
public:
	CEffect() {
		type = STATIC_OBJECT;
		killBySimon = false;
	}
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	bool GetLastFrame();
	void reset();
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
	TYPE_MAKE_ITEM GetMakeItem() {
		return type;
	}
};

typedef CEffect* LPEFT;