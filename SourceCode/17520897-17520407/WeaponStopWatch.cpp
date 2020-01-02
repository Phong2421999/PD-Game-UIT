#pragma once
#include "WeaponStopWatch.h"
#include "SoundController.h"
WeaponStopWatch::WeaponStopWatch()
{
	health = 1;
	makeTime = GetTickCount();
	SoundController::Play(STOPWATCH_SOUND_ID);
}

void WeaponStopWatch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	DWORD now = GetTickCount();
	/*if (now - makeTime > HOLY_WATER_WEAPON_TIME_LIVE)
	{
		health = 0;
	}*/
}