#include "WeaponEnemies.h"
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