#include "CMap.h"
CMap * CMap::__instance = NULL;

CMap *CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}

void CMap::Add(int mapId, LPCSTR mapPath, int texId, LPCSTR texPath, D3DCOLOR color)
{
	CTiles* map = new CTiles(texId, texPath, color);
	maps[mapId] = map;
	maps[mapId]->ReadMapTXT(mapPath);
	DebugOut(L"[INFO] Add filepath Success\n");
}

LPTILES CMap::Get(int mapId) {
	return maps[mapId];
}
