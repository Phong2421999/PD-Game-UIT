#include "CAnimation.h"


void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				lastFrame = true;
				currentFrame = 0;
			}
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

bool CAnimation::getLastFrame()
{
	return lastFrame;
}

int CAnimation::getCurrentFrame()
{
	return currentFrame;
}
void CAnimation::setIsLastFrame(bool l)
{
	this->lastFrame = l;
}

void CAnimation::reset()
{
	this->currentFrame = -1;
	lastFrame = false;
}