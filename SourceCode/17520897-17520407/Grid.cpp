#include "Grid.h"


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

void Grid::getListObjects(vector<LPGAMEOBJECT> &objects)
{
	vector<int> gridData;
	caculateGrid(gridData);
	for (int i = 0; i < gridData.size(); i++)
	{
		vector<LPGAMEOBJECT> temp;
		get(gridData[i], temp);
		for (int i = 0; i < temp.size(); i++)
		{
			objects.push_back(temp[i]);
		}
	}
}

void Grid::caculateGrid(vector<int> &gridData)
{
	float gridSize = (SCREEN_WIDTH + 2 * GRID_OFFSET) / GRID_PART;
	float cx = CGame::GetInstance()->GetCamPos_x();
	float beginGridPos = abs(cx - GRID_OFFSET);
	float endGridPos = abs(cx + SCREEN_WIDTH + GRID_OFFSET);

	int beginGrid = floor(beginGridPos / gridSize);
	int endGrid = ceil(endGridPos / gridSize);
	gridData.clear();
	for (int i = beginGrid; i <= endGrid; i++)
	{
		if (gridObjects[i].size() > 0)
			gridData.push_back(i);
	}
	gridData.push_back(-1);
}

