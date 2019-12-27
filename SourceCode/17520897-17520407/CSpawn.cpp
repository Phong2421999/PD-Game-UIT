#include "CSpawn.h"



void CSpawn::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
		if (IsTouchSimon())
		{
			
				CSpawner *spawner = CSpawner::GetInstance();
				if (spawner->spawnerId != this->spawnerId)
				{
					spawner->Reset();
				}
				if (spawner->isActive)
				{
					spawner->canRespawn = this->canRespawn;
					spawner->xEnemy = this->xEnemy;
					spawner->yEnemy = this->yEnemy;
					spawner->enemyId = this->enemyId;
					spawner->quantityEachSpawn = this->quantityEachSpawn;
					spawner->spawnerId = this->spawnerId;
					spawner->delaySpawnTime = this->delaySpawnTime;
					spawner->timeEachSpawn = this->timeEachSpawn;
					spawner->canSpawn = true;
					spawner->offsetWithSimon = this->offsetWithSimon;
					spawner->setBoss = this->setBoss;
					spawner->setBoss ? DebugOut(L"\nBoss") : DebugOut(L"\nEnemy");
					spawner->xTarget = this->xTarget;
					spawner->yTarget = this->yTarget;
				}
		}
}

bool CSpawn::IsTouchSimon() {
	CSimon* simon = CSimon::getInstance();
	if (checkAABBTouch(simon))
		return true;

	LPCOLLISIONEVENT collitionEvent = this->SweptAABBEx(simon);
	if (collitionEvent->t >= 0 && collitionEvent->t <= 1.0f)
		return true;

	return false;
}

void CSpawn::Render() {
	RenderBoundingBox(x, y);
}

void CSpawn::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}
