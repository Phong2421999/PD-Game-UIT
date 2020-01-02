#pragma once
#include "HiddenObjects.h"
#include "Simon.h"
#include "GameConst.h"

class IntroGate :public HiddenObjects
{
private:
	DWORD timeTocuhSimon;
	bool isTouchSimon;
public:
	IntroGate(){
		isTouchSimon = false;
	}
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
};
