#include "Wall.h"


void CWall::Render()
{
	RenderBoundingBox(x, y);
}

void CWall::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
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
			if (simon->getOnGround())
			{
				if (simon->x + 16 <= x)
				{
					if (simon->nx > 0)
						simon->vx = -0.0005;
				}
				else if(simon->x + 16 >= x)
				{
					if (simon->nx < 0)
						simon->vx = 0.0005;
				}

				/*if (simon->nx > 0)
				{
					if (simon->x + 16 >= x)
						simon->vx = 0.0005;
					else
						simon->vx = -0.005;
				}
				else
				{
					if (simon->x + 16 <= x)
						simon->vx = -0.0005;
					else
						simon->vx = 0.005;
				}*/
			}
			else
			{
				simon->vx = 0;
			}
			/*if (nx != simonNx)
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
				nx = -simonNx;*/
		}


	}

}