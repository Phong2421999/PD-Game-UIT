#include "Scenes.h"

Scenes* Scenes::__instance = NULL;

Scenes* Scenes::GetInstance()
{
	if (__instance == NULL)
		__instance = new Scenes();
	return __instance;
}