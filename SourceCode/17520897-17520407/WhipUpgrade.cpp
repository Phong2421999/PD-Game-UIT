#include "WhipUpgrade.h"


WhipUpgrade::WhipUpgrade() {
	this->AddAnimation(ANI_WHIP_UPGRADE);
	makeTime = GetTickCount();
	health = 1;
	type = WHIP_UPGRADE;
}

void WhipUpgrade::Render() {
	animations[0]->Render(x, y);
	RenderBoundingBox(x,y);
}

void WhipUpgrade::RenderCurrentFrame()
{
	animations[0]->RenderCurrentFrame(x, y);
}

void WhipUpgrade::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects){
	CItems::Update(dt, coObjects);
	DWORD now = GetTickCount();
	if (now - makeTime > WHIP_UPGRADE_TIME_LIVE)
	{
		health = 0;
	}
}

void WhipUpgrade::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}