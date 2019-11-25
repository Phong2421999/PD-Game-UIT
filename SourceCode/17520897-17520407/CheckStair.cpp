#include "CheckStair.h"

void CheckStair::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CheckStair::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	
		CSimon* simon = CSimon::getInstance();
		if (this->isTouchOtherObject(simon))
		{
			float sx, sy;
			simon->GetPosition(sx, sy);
			simon->setStairType(type);
			simon->setStairActiveNy(this->ny);
			float checkPosition = 0;
			if (this->nx > 0)
			{
				checkPosition = x - (sx + 16);
			}
			else
			{
				checkPosition = sx + 16 - x;
			}
			if (checkPosition > 0
				&& simon->getOnStair()
				&& simon->getAutoGoToStair() == false
				&& simon->getCanSetStair())
			{
				simon->setAutoGoToStair(true);
				isSetAutoGoStair = true;
				simon->setStairNx(this->nx);
				simon->setStairNy(this->ny);
				simon->nx = this->nx;
				simon->ny = this->ny;

				simon->setAutoGoDistance(abs(checkPosition - 2));

				simon->setCanSetStair(false);

			}
			else if (checkPosition <= 0
				&& simon->getOnStair()
				&& isSetAutoGoStair == false
				&& simon->getAutoGoToStair() == false
				&& simon->getCanSetStair())
			{
				simon->setAutoGoToStair(true);
				simon->setAutoGoDistance(abs(checkPosition + width / 1.2));
				simon->setStairNx(this->nx);
				simon->setStairNy(this->ny);
				simon->ny = this->ny;
				if (this->nx > 0)
				{
					if (simon->nx > 0)
						simon->nx = -1;
				}
				else
				{
					if (simon->nx < 0)
						simon->nx = 1;
				}
			}
		}
		else
		{
			isSetAutoGoStair = false;
		}

}

void CheckStair::Render()
{
	this->RenderBoundingBox(x, y);
}