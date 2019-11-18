#include "CheckStair.h"

void CheckStair::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CheckStair::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	for (int i = 0; i < coObjects->size(); i++)
	{
		CSimon* simon = CSimon::getInstance();
		if (this->isTouchOtherObject(simon))
		{
			float sx, sy;
			simon->GetPosition(sx, sy);
			simon->setStairType(type);
			simon->setStairNy(this->ny);
			float checkPosition = 0;
			if (this->nx > 0)
			{
				checkPosition = x - (sx + 16);
			}
			else
			{
				checkPosition = sx + 16 - x;
			}
			if (checkPosition >= 0
				&& simon->getOnStair()
				&& isSetAutoGoStair == false
				&& simon->getAutoGoToStair() == false
				&& simon->getCanSetStair())
			{
				simon->setAutoGoToStair(true);
				isSetAutoGoStair = true;
				simon->nx = this->nx;
				simon->ny = this->ny;
				// cho x simon đến giữa stair => -8 đưa animation simon ra giữa stair để flip hoặc đi
				if (this->nx > 0)
					simon->setAutoGoDistance(checkPosition + width / 2 - 8 - 2); //-2 vì nx>0 dịch ra 2 pixel để đứng chuẩn stair
				else
					simon->setAutoGoDistance(checkPosition + width / 2 - 8 + 2); //+2 vì nx<0 dịch ra 2 pixel để đứng chuẩn stair
				simon->setStairNx(this->nx);
				simon->setCanSetStair(false);
			}
			else if (checkPosition < 0
				&& simon->getOnStair()
				&& isSetAutoGoStair == false
				&& simon->getAutoGoToStair() == false
				&& simon->getCanSetStair())
			{
				simon->setAutoGoToStair(true);
				simon->setAutoGoDistance(width / 2); // cho đi ra quá nữa cầu thang câu if trên sẽ lo tiếp
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
}

void CheckStair::Render()
{
	this->RenderBoundingBox(x, y);
}