#pragma once
#include "CEnemies.h"
#define ANI_GHOST 565

class CGhost:public CEnemies {
private:
	int width, height;
public:
	CGhost();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};