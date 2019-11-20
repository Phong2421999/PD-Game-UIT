#include "Grid.h"

Grid * Grid::__instance = NULL;

Grid * Grid::GetInstance() {
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}

void Grid::checkGrid(vector<CGameObject*>objects, vector<CGameObject*>&returnObject)
{
	returnObject.clear();
	float cx;
	cx = CGame::GetInstance()->GetCamPos_x();
	float leftCheck = cx - 48;
	float rightCheck = cx + SCREEN_WIDTH + 48;
	for (int i = 0; i < objects.size(); i++)
	{
		float x, y;
		objects[i]->GetPosition(x, y);
		if (objects[i]->GetHealth() > 0)
		{
			if (x >= leftCheck && x <= rightCheck || x <= -150)
			{
				returnObject.push_back(objects[i]);
			}
		}
		else
		{
			objects.erase(objects.begin() + i);
		}
		
	}
}
