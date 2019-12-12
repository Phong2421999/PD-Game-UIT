#include "Grid.h"

Grid * Grid::__instance = NULL;

Grid * Grid::GetInstance() {
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}



void Grid::add(LPGAMEOBJECT obj, int grid)
{
	gridObjects[grid].push_back(obj);
}


void Grid::clear()
{
	gridObjects.clear();
}

void Grid::get(int grid, vector<LPGAMEOBJECT> &objects)
{
	objects = gridObjects[grid];
}

void Grid::caculateGrid(vector<int> &gridData)
{
	float gridSize = (SCREEN_WIDTH + 2 * GRID_OFFSET)/GRID_PART;
	float cx = CGame::GetInstance()->GetCamPos_x();
	float beginGridPos = abs(cx - GRID_OFFSET);
	float endGridPos = abs(cx + SCREEN_WIDTH + GRID_OFFSET);

	int beginGrid = floor( beginGridPos / gridSize);
	int endGrid = ceil(endGridPos / gridSize);
	gridData.clear();
	for (int i = beginGrid; i <= endGrid; i++)
	{
		if(gridObjects[i].size()>0)
			gridData.push_back(i);
		if (i == endGrid)
			gridData.push_back(-1);
	}
}
void Grid::eraseObject(int gridId, int index)
{
	gridObjects[gridId].erase(gridObjects[gridId].begin() + index);
}

