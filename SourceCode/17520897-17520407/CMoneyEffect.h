#pragma once
#include "CEffect.h"
#define ANI_RED_BAG_EFFECT 1546
#define ANI_PURPLE_BAG_EFFECT 1547
#define ANI_WHITE_BAG_EFFECT 1647

#define ANI_RED_BAG_EFFECT_ID 0
#define ANI_PURPLE_BAG_EFFECT_ID 1
#define ANI_WHITE_BAG_EFFECT_ID 2

class CMoneyEffect :public CEffect {
private:
	int ani;
public:
	CMoneyEffect(float x, float y,GAME_ITEM moneyType);
	void Render();

};