#include"StopWatch.h"

StopWatch::StopWatch(float x, float y)
{
	this->AddAnimation(ANI_STOP_WATCH);
	this->x = x;
	this->y = y;
	this->width = STOP_WATCH_WIDTH;
	this->height = STOP_WATCH_HEIGHT;
	type = STOP_WATCH_ITEM;
	makeTime = GetTickCount();
}


void StopWatch::Render() {
	animations[ANI_STOP_WATCH_ID]->Render(x, y);
	RenderBoundingBox(x, y);
}

void StopWatch::RenderCurrentFrame() {
	animations[ANI_STOP_WATCH_ID]->RenderCurrentFrame(x, y);
}

void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItems::Update(dt, coObjects);

	DWORD now = GetTickCount();
	if (now - makeTime > STOP_WATCH_TIME_LIVE)
	{
		health = 0;
	}
}

void StopWatch::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}