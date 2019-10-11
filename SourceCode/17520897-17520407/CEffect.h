#pragma once
#include "./FrameWork/GameObject.h"

class CEffect : public CGameObject {
public:
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	bool GetLastFrame();
};

typedef CEffect* LPEFT;