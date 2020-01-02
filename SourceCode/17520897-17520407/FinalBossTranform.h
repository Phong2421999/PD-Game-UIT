#pragma once
#include "CEffect.h"
#define FINAL_BOSS_ANI_TRANSFROM_ID 300531
#define TRANSFORM_EFFECT_LEFT 0
#define TRANSFORM_EFFECT_RIGHT 1
#define TRANSFORM_EFFECT_TOP 2
#define TRANSFORM_EFFECT_BOTTOM 3
#define TRANSFORM_EFFECT_LEFT_TOP 4
#define TRANSFORM_EFFECT_LEFT_BOTTOM 5
#define TRANSFORM_EFFECT_RIGHT_TOP 6
#define TRANSFORM_EFFECT_RIGHT_BOTTOM 7



class FinalBossTransform :public CEffect {
private:
	float vxPlus, vyPlus;
	int effectType;
public:
	FinalBossTransform();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void SetPlusVelocity(float x, float y)
	{
		this->vxPlus = x;
		this->vyPlus = y;
	}
	void SetEffectType(int i)
	{
		this->effectType = i;
		if (effectType == TRANSFORM_EFFECT_LEFT)
		{
			vxPlus = -vxPlus;
			vyPlus = 0;
		}
		else if (effectType == TRANSFORM_EFFECT_RIGHT)
		{
			vyPlus = 0;
		}
		else if (effectType == TRANSFORM_EFFECT_TOP)
		{
			vxPlus = 0;
			vyPlus = -vyPlus;
		}
		else if (effectType == TRANSFORM_EFFECT_BOTTOM)
		{
			vxPlus = 0;
		}
		else if (effectType == TRANSFORM_EFFECT_LEFT_TOP)
		{
			vxPlus = -vxPlus;
			vyPlus = -vyPlus;
		}
		else if (effectType == TRANSFORM_EFFECT_LEFT_BOTTOM)
		{
			vxPlus = -vxPlus;
		}
		else if (effectType == TRANSFORM_EFFECT_RIGHT_TOP)
		{
			vyPlus = -vyPlus;
		}
		DebugOut(L"\nVxP: %f, VyP: %f", vxPlus, vyPlus);
	}
};
