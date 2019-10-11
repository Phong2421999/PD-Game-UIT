#pragma once
#include "Weapon.h"

#define WHIP_SPEED_X 0
#define WHIP_SPEED_Y 0
#define WHIP_BBOX_HEIGHT 6
#define WHIP_BBOX_LEVEL1_WIDTH 25
#define WHIP_BBOX_LEVEL2_WIDTH 25
#define WHIP_BBOX_LEVEL3_WIDTH 40

#define WHIP_TIME_LIVE 100


class Whip : public Weapon {
public :
	Whip(float x, float y, int nx);
};