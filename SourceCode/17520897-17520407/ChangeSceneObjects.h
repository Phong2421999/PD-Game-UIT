#pragma once
#include "Simon.h"
#include "CStaticObject.h"

#define ANI_DOOR 561

class ChangeSceneObjects : public CStaticObject {
private:
	int sceneId;
	float simonAutoGoDistance;
	bool simonAutoGo;

	bool camAutoGo;
	bool isCanRender;
	bool isDoor;
	CSimon* simon;
	int changeSceneObjectIndex;
public:
	ChangeSceneObjects()
	{
		simon = CSimon::getInstance();
		simonAutoGoDistance = 0;
		simonAutoGo = false;
		isDoor = false;
		this->AddAnimation(ANI_DOOR);
		changeSceneObjectIndex = 0;
		camAutoGo = false;
		isCanRender = true;
	}
	void SetWidthHeight(float width, float height)
	{
		this->width = width;
		this->height = height;
	}
	void SetCamAutoGo(bool b)
	{
		this->camAutoGo = b;
	}
	void SetIsDoor(bool b)
	{
		this->isDoor = b;
	}
	void SetAutoGoDistance(float dis)
	{
		this->simonAutoGoDistance = dis;
	}
	void SetSimonAutoGo(bool autoGo)
	{
		this->simonAutoGo = autoGo;
	}
	void SetSceneId(int sceneId)
	{
		this->sceneId = sceneId;
	}
	void SetChangeSceneObjectIndex(int i)
	{
		this->changeSceneObjectIndex = i;
	}
	int GetChangeSceneObjectIndex()
	{
		return changeSceneObjectIndex;
	}
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom)
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
};