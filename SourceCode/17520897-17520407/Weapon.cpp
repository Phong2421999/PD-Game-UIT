#include "Weapon.h"
void Weapon::Render()
{
	//animations[0]->Render(x, y);
	RenderBoundingBox(x,y);
}

void Weapon::RenderFlipX()
{
	//animations[0]->RenderFlipX(x, y);
	RenderBoundingBox(x, y);
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
				if (dynamic_cast<CEnemies*>(coObjects->at(i)) 
					|| dynamic_cast<CStaticObject*>(coObjects->at(i)))
				{
					coObjects->at(i)->Damage(1);
					coObjects->at(i)->SetKillBySimon(true);
				}
			}
		}
	}
}

void Weapon::SetPositionWithSimon(float x, float y, int nx)
{
	if (nx > 0)
	{
		SetPosition(x + OFFSET_X_TO_HAND_RIGHT_SIMON, y + OFFSET_Y_TO_HAND_SIMON);
	}
	else
	{
		SetPosition(x - OFFSET_X_TO_HAND_LEFT_SIMON, y + OFFSET_Y_TO_HAND_SIMON);
	}
}

void Weapon::SetIsJump(bool b) // vũ khí di chuyển theo simon khi đang nhảy
{
	this->isJump = b;
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