#include "CSpawn.h"



void CSpawn::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (IsTouchSimon(coObjects->at(i)))
		{
			if (dynamic_cast<CSimon*>(coObjects->at(i)))
			{
				simonHasTouch = true;
				if (CSpawner::GetInstance()->spawnerId != this->spawnerId)
				{
					CSpawner::GetInstance()->reset();
				}
				CSpawner::GetInstance()->enemyId = this->enemyId;
				CSpawner::GetInstance()->quantityEachSpawn = this->quantityEachSpawn;
				CSpawner::GetInstance()->spawnerId = this->spawnerId;
			}
		}
	}
}

bool CSpawn::IsTouchSimon(LPGAMEOBJECT gameObject) {

	if (checkAABBTouch(gameObject))
		return true;

	LPCOLLISIONEVENT collitionEvent = this->SweptAABBEx(gameObject);
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
