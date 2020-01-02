#pragma once
#include "CEffect.h"
#define ANI_HIT 564
#define ANI_HIT_ID 0

#define HITEFFECT_SOUND_ID 18

class CHit:public CEffect {

public:
	CHit();
	void Reset()
	{
		animations[ANI_HIT_ID]->reset();
	}
	void Render();
};