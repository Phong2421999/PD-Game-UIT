#include "FrameWork/GameObject.h"
#include "FrameWork/Game.h"
#include "CEnemies.h"
#include "CSpawn.h"

#define DESTROY_WIDTH 8
#define DESTROY_HEIGHT 260

#define DESTROY_BOTTOM_WIDTH 320
#define DESTROY_BOTTOM_HEIGHT 8

#define DESTROY_OFFSET_LEFT  8
#define DESTROY_OFFSET_RIGHT -8

class CDestroy:public CGameObject
{
private:
	int width, height;
	TYPE_DESTROY_ITEM type;
public:
	CDestroy()
	{
		type = LEFT;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool IsTouchOtherColision(LPGAMEOBJECT gameObject);
	void SetType(TYPE_DESTROY_ITEM type) {
		this->type = type;
		if (type == BOTTOM)
		{
			width = DESTROY_BOTTOM_WIDTH;
			height = DESTROY_BOTTOM_HEIGHT;
		}
		else
		{
			width = DESTROY_WIDTH;
			height = DESTROY_HEIGHT;
		}


	}
	TYPE_DESTROY_ITEM GetType()
	{
		return type;
	}
};
