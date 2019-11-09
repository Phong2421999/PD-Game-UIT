#include "CDestroy.h"


void CDestroy::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	y = CGame::GetInstance()->GetCamPos_y();

	if (type == LEFT) {
		x = CGame::GetInstance()->GetCamPos_x() - DESTROY_OFFSET_LEFT;
	}
	else
	{
		x = CGame::GetInstance()->GetCamPos_x() + SCREEN_WIDTH + DESTROY_OFFSET_RIGHT;
	}
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (IsTouchOtherColision(coObjects->at(i)))
		{
			if (dynamic_cast<CEnemies*>(coObjects->at(i)))
			{
				CEnemies* enemy = dynamic_cast<CEnemies*>(coObjects->at(i));
				if(enemy->GetActive())
					coObjects->at(i)->Damage(1);
			}
		}
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