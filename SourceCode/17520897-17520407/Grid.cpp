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

vector<LPGAMEOBJECT> Grid::get(int grid)
{
	return gridObjects[grid];
}

int caculateGrid(float x)
{
	float gridSize = (SCREEN_WIDTH + 2 * GRID_OFFSET)/GRID_PART;
	int grid = floor(x / gridSize);
	return grid;
}