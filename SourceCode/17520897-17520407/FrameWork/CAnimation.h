#pragma once
#include <d3dx9.h>
#include "CSprites.h"
#include "CAnimationFame.h"

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	bool lastFrame;
	bool nextIsLastFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) {
		this->defaultTime = defaultTime;
		lastFrameTime = -1;
		currentFrame = 0;
		nextIsLastFrame = false;
		lastFrame = false;
	}
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha = 255);
	void RenderCurrentFrame(float x, float y, int alpha = 255);
	void RenderCurrentFrameFlipX(float x, float y,float offset, int alpha = 255);
	
	bool getLastFrame();
	bool getNextIsLastFrame();
	int getCurrentFrame();
	void setIsLastFrame(bool l);
	void reset();
	void RenderFlipX(float x, float y, float offsetX, int alpha = 255);
};


typedef CAnimation *LPANIMATION;

