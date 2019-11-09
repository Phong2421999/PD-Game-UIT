#include "FrameWork/GameObject.h"
#include "FrameWork/Game.h"
#include "CEnemies.h"
#include "CSpawn.h"

#define DESTROY_WIDTH 8
#define DESTROY_HEIGHT 260

class CDestroy:public CGameObject
{
private:
	int width, height;
	TYPE_DESTROY_ITEM type;
public:
	CDestroy()
	{
		type = LEFT;
		width = DESTROY_WIDTH;
		height = DESTROY_HEIGHT;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	bool IsTouchOtherColision(LPGAMEOBJECT gameObject);
	void SetType(TYPE_DESTROY_ITEM type) {
		this->type = type;
	}
	TYPE_DESTROY_ITEM GetType()
	{
		return type;
	}
};
