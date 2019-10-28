#include "ChangeSceneObjects.h"

void ChangeSceneObjects::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CSimon*> (coObjects->at(i)))
		{
			if (this->checkAABBTouch(coObjects->at(i)))
			{
				simon->setSceneId(this->sceneId);
			}
		}
	}
}