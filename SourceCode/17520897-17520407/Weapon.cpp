#include "Weapon.h"
void Weapon::Render()
{
	//animations[0]->Render(x, y);
	RenderBoundingBox();
}

void Weapon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x; 
	top = y; 
	right = x + width; 
	bottom = y + height;

}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (coObjects->size() >= 0)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (isTouchOtherObject(coObjects->at(i)))
			{
				if (dynamic_cast<CTestEnemy*>(coObjects->at(i)))
				{
					coObjects->at(i)->Damage();
				}
			}
		}
	}
}

bool Weapon::isTouchOtherObject(LPGAMEOBJECT gameObject)
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