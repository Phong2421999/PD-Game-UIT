#pragma once
#include "WeaponStopWatch.h"

WeaponStopWatch::WeaponStopWatch()
{
	DebugOut(L"\nNgung dong thoi gian o day\n");
	health = 1;
	makeTime = GetTickCount();
}

void WeaponStopWatch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	DWORD now = GetTickCount();
	if (now - makeTime > HOLY_WATER_WEAPON_TIME_LIVE)
	{
		health = 0;
	}
}