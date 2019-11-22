#pragma once
#include "CItems.h"
#define ANI_MAGIC_CRYSTAL 556
#define ANI_MAGIC_CRYSTAL_ID 0

#define MAGIC_CRYSTAL_WIDTH 14
#define MAGIC_CRYSTAL_HEIGHT 16

#define MAGIC_CRYSTAL_GRAVITY 0.0005

class MagicCrystal :public CItems
{
private:
	int width, height, ani;
	DWORD makeTime;
public:
	MagicCrystal(float x, float y);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);

};