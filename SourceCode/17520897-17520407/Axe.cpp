#include"Axe.h"


Axe::Axe(float x, float y)
{
	this->AddAnimation(ANI_AXE);
	this->x = x;
	this->y = y;
	this->width = AXE_WIDTH;
	this->height = AXE_HEIGHT;
	type = AXE_ITEM;
	makeTime = GetTickCount();
}


void Axe::Render() {
	animations[ANI_AXE_ID]->Render(x, y);
	RenderBoundingBox(x, y);
}

void Axe::RenderCurrentFrame() {
	animations[ANI_AXE_ID]->RenderCurrentFrame(x, y);
}

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	vy += GRAVITY * dt;
	CItems::Update(dt, coObjects);

	DWORD now = GetTickCount();
	if (now - makeTime > AXE_TIME_LIVE)
	{
		health = 0;
	}
}

void Axe::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}