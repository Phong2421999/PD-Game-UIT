#include "WhipUpgrade.h"


WhipUpgrade::WhipUpgrade() {
	this->AddAnimation(ANI_WHIP_UPGRADE);
	makeTime = GetTickCount();
	type = WHIP_UPGRADE;
}

void WhipUpgrade::Render() {
	animations[ANI_WHIP_ID]->Render(x, y);
	RenderBoundingBox(x,y);
}

void WhipUpgrade::RenderCurrentFrame()
{
	animations[ANI_WHIP_ID]->RenderCurrentFrame(x, y);
}

void WhipUpgrade::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects){
	vy += WHIP_UPGRADE_GRAVITY * dt;
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