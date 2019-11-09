#include "Spawner.h"

CSpawner * CSpawner::__instance = NULL;

CSpawner * CSpawner::GetInstance() {
	if (__instance == NULL)
		__instance = new CSpawner();
	return __instance;
}