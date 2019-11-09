#include "CAnimation.h"


void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::RenderCurrentFrame(float x, float y, int alpha) {
	if (currentFrame == frames.size())
		currentFrame = 0;
	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

void CAnimation::RenderCurrentFrameFlipX(float x, float y,float offset, int alpha) {
	if (currentFrame == frames.size())
		currentFrame = 0;
	frames[currentFrame]->GetSprite()->DrawFlipX(x, y, offset, alpha);
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
			if (currentFrame + 1 == frames.size())
			{
				nextIsLastFrame = true;
			}
			if (currentFrame == frames.size()) {
				lastFrame = true;
				nextIsLastFrame = false;
				currentFrame = 0;
			}
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

void CAnimation::RenderFlipX(float x, float y, float offsetX, int alpha)
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
			if (currentFrame + 1 == frames.size())
			{
				nextIsLastFrame = true;
			}
			if (currentFrame == frames.size()) {
				lastFrame = true;
				nextIsLastFrame = false;
				currentFrame = 0;
			}
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}

	}

	frames[currentFrame]->GetSprite()->DrawFlipX(x, y, offsetX, alpha);
}

bool CAnimation::getLastFrame()
{
	return lastFrame;
}

bool CAnimation::getNextIsLastFrame()
{
	return nextIsLastFrame;
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
	this->currentFrame = 0;
	lastFrame = false;
}