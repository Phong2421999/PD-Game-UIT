#include "CMap.h"
CMap * CMap::__instance = NULL; 

CMap *CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}

void CMap::Add( int id, LPCSTR filePath, int texId )
{
	CTiles* map = new CTiles(filePath, texId);
	maps[id] = map;
	DebugOut(L"[INFO] Add filepath Success\n");
}

LPTILES CMap::Get(int id) {
	return maps[id];
}
