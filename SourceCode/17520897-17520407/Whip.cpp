#include "Whip.h"

Whip::Whip(float x, float y, int nx)
{
	SetSpeed(WHIP_SPEED_X, WHIP_SPEED_Y);
	SetWidthHeigth(WHIP_BBOX_LEVEL1_WIDTH, WHIP_BBOX_HEIGHT);
	SetTimeLive(WHIP_TIME_LIVE);
	SetPositionWithSimon(x, y, nx);
}

