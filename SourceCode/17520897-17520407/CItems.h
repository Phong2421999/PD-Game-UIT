#pragma once
#include "FrameWork/GameObject.h"

class CItems : public CGameObject {
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
};