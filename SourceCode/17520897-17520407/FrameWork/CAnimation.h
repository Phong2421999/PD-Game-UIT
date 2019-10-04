#pragma once
#include <d3dx9.h>
#include "CSprites.h"
#include "CAnimationFame.h"

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha = 255);
	void Flip(float FlipX, float FlipY) {
		for (int i = 0; i < frames.size(); i++)
		{
			frames[i]->Flip(FlipX, FlipY);
		}
	}
};

typedef CAnimation *LPANIMATION;

