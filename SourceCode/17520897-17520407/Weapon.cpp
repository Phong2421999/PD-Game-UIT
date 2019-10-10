#include "Weapon.h"
#include "FrameWork/debug.h"
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
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	/*vector<int> t;
	for (int i = 0; i <= coObjects->size(); i++)
	{
		float ml, mt, mr, mb;
		float sl, st, sr, sb;
		GetBoundingBox(ml, mt, mr, mb);
		coObjects->at(i)->GetBoundingBox(sl, st, sr, sb);
		float t;
		float nx, ny;
		CGame::SweptAABB(ml, mt, mr, mb, vx*dt, vy*dt, sl, st, sr, sb, t, nx, ny);
	}*/

	/*if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CEnemies*>(e->obj))
			{
				DELETE_POINTER(e);
				OutputDebugString(L"attack enemy");
			}

		}
	}*/
}