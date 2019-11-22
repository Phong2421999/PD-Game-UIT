#pragma once
#include "CItems.h"
#define ANI_INVI_POTION 554
#define ANI_INVI_POTION_ID 0

#define INVI_POTION_WIDTH 13
#define INVI_POTION_HEIGHT 16

#define INVI_POTION_TIME_LIVE 2000

#define INVI_POTION_GRAVITY 0.0005

class InviPotion :public CItems
{
private:
	int width, height, ani;
	DWORD makeTime;
public:
	InviPotion(float x, float y);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

};