#pragma once
#include "CEffect.h"
#define ANI_SPLASH 563
#define ANI_SPLASH_ID 0

#define SPLASH_Y_CENTER 160
#define SPLASH_Y_SIDE 180

#define SPLASH_OFFSET_LEFT 8
#define SPLASH_OFFSET_RIGHT 16

#define SPLASH_VELOCITY_X 0.02
#define SPLASH_VELOCITY_y 0.02
#define SPLASH_GRAVITY 0.0003

#define SPLASH_OFFSET_X 8

#define QUANTITY_EFFECT_SPLASH 3

class CSplash :public CEffect {

public:
	CSplash(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects);
};