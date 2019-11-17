#include "WeaponEnemies.h"
void WeaponEnemies::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (coObjects->size() >= 0)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (isTouchOtherObject(coObjects->at(i)))
			{
				if (dynamic_cast<CSimon*>(coObjects->at(i)))
				{
					coObjects->at(i)->Damage(1);
					health = 0;
				}
			}
		}
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