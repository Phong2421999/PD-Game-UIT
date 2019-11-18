#include "Wall.h"


void CWall::Render()
{
	RenderBoundingBox(x, y);
}

void CWall::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CSimon*>(coObjects->at(i)))
		{
			CSimon* simon = CSimon::getInstance();
			float left, top, right, bottom;
			float simonLeft, simonTop, simonRight, simonBottom;

			int simonNx = simon->getDirection();
			float simonX, simonY;
			if (this->isTouchOtherObject(simon))
			{
				if (simon->getOnStair() == false)
				{
					simon->GetPosition(simonX, simonY);
					if (nx != simonNx)
					{
						if (this->y > simon->y)
						{
							if (simonNx > 0)
							{
								simon->vx = -0.002;
							}
							else
							{
								simon->vx = 0.002;
							}
						}
						else
							simon->vx = 0;
					}
					else
						nx = -simonNx;
				}


			}
		}
	}
}