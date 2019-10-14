#pragma once
#include "CItems.h"
#define ANI_DANGER 543
#define ANI_DANGER_ID 0

#define DANGER_WIDTH 17
#define DANGER_HEIGHT 12

#define DANGER_TIME_LIVE 2000

#define DANGER_GRAVITY 0.0005

class Danger :public CItems
{
private:
	int width, height;
	DWORD makeTime;
public:
	Danger();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};