#include "CItems.h"
#define ANI_HOLY_WATER 549
#define ANI_HOLY_WATER_ID 0

#define HOLY_WATER_WIDTH 15
#define HOLY_WATER_HEIGHT 16

#define HOLY_WATER_TIME_LIVE 2000

class HolyWater : public CItems
{
private:
	int width, height;
	DWORD makeTime;
public:
	HolyWater(float x, float y);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();
	void RenderCurrentFrame();
	void SetMakeTime(DWORD time)
	{
		this->makeTime = time;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void SetWidthHeight(int width, int height) {
		this->width = width;
		this->height = height;
	}
};
