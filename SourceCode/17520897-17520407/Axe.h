#include "CItems.h"
#define ANI_AXE 544
#define ANI_AXE_ID 0

#define AXE_WIDTH 15
#define AXE_HEIGHT 15

#define AXE_TIME_LIVE 2000

class Axe: public CItems
{
private:
	int width, height;
	DWORD makeTime;
public:
	 Axe(float x, float y);
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
