#pragma once
#include "Weapon.h"
#include "Simon.h"
#define STOPWATCH_SOUND_ID 13
class WeaponStopWatch : public Weapon {
private:
	DWORD makeTime;
public:
	WeaponStopWatch();
	void Render() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
};