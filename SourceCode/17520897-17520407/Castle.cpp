#include "Castle.h"

Castle::Castle() {
	this->AddAnimation(CASTLE_ANI);
	this->AddAnimation(CASTLE_IDLE_ANI);
	ani = 0;
}


void Castle::Render() {
	animations[ani]->Render(x, y);
	RenderBoundingBox(x, y);
}


void Castle::RenderCurrentFrame() {
	animations[ani]->RenderCurrentFrame(x, y);
}

void Castle::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	
}

void Castle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (animations[0]->getLastFrame())
	{
		ani = 1;
	}
}