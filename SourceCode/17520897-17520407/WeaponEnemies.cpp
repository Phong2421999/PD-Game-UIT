#include "WeaponEnemies.h"
void WeaponEnemies::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CSimon* simon = CSimon::getInstance();
	if (isTouchOtherObject(simon))
	{
		simon->Damage(1);
		simon->TouchEnemy(this->nx);
		health = 0;
	}
}

bool WeaponEnemies::isTouchOtherObject(LPGAMEOBJECT gameObject)
{
	if (gameObject->health <= 0)
		return false;

	if (checkAABBTouch(gameObject))
		return true;

	LPCOLLISIONEVENT collitionEvent = this->SweptAABBEx(gameObject);
	if (collitionEvent->t >= 0 && collitionEvent->t <= 1.0f)
		return true;

	return false;
}