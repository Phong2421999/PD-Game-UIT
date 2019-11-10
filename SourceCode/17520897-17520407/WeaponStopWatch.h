#pragma once
#include "Weapon.h"
#include "Simon.h"
class WeaponStopWatch : public Weapon {
private:
	DWORD makeTime;
public:
	WeaponStopWatch();
	void Render() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
};