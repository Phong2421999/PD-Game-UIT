#include "LockSimon.h"


void LockSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CSimon* simon = CSimon::getInstance();
	if (this->checkAABBTouch(simon))
	{
		float vx, vy;
		simon->GetSpeed(vx, vy);
		simon->SetSpeed(vx, 0);
		simon->setLock(true);
	}
	else
		simon->setLock(false);
}

void LockSimon::Render()
{
	RenderBoundingBox(x, y);
}
