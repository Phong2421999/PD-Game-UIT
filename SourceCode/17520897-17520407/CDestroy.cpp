#include "CDestroy.h"
#include "Weapon.h"
#include "WeaponEnemies.h"

void CDestroy::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (type == LEFT) {
		x = CGame::GetInstance()->GetCamPos_x() - DESTROY_OFFSET_LEFT;
		y = CGame::GetInstance()->GetCamPos_y();
	}
	else if (type == RIGHT)
	{
		x = CGame::GetInstance()->GetCamPos_x() + SCREEN_WIDTH + DESTROY_OFFSET_RIGHT;
		y = CGame::GetInstance()->GetCamPos_y();
	}
	else
	{
		x = CGame::GetInstance()->GetCamPos_x();
	}


	for (int i = 0; i < coObjects->size(); i++)
	{
		if (IsTouchOtherColision(coObjects->at(i)))
		{
			CEnemies* enemy = dynamic_cast<CEnemies*>(coObjects->at(i));
			if (dynamic_cast<CEnemies*>(enemy))
			{
				if (enemy->GetActive())
				{
					coObjects->at(i)->health = -1;
				}
			}
			if (dynamic_cast<Weapon*>(coObjects->at(i))
				|| dynamic_cast<WeaponEnemies*>((coObjects)->at(i)))
			{
				coObjects->at(i)->health = -1;
			}
		}
	}

	CSimon* simon = CSimon::getInstance();
	if (IsTouchOtherColision(simon) && simon->getDeath() == false)
	{
		int live = simon->getLive() - 1;
		simon->setLive(live);
		simon->health = 0;
		simon->setDeath(true);
		simon->setStartDeathTime(GetTickCount());
		state = SIMON_STATE_DIE;
	}
}
bool CDestroy::IsTouchOtherColision(LPGAMEOBJECT gameObject) {

	if (checkAABBTouch(gameObject))
		return true;

	LPCOLLISIONEVENT collitionEvent = this->SweptAABBEx(gameObject);
	if (collitionEvent->t >= 0 && collitionEvent->t <= 1.0f)
		return true;

	return false;
}

void CDestroy::Render() {
	RenderBoundingBox(x, y);
}

void CDestroy::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}