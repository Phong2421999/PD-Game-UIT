#pragma once
#include "Simon.h"
#include "CStaticObject.h"

#define ANI_DOOR_OPNEN 561
#define ANI_DOOR_CLOSE 5611


class ChangeSceneObjects : public CStaticObject {
private:
	int sceneId;
	float simonAutoGoDistance;
	bool simonAutoGo;

	bool camAutoGo;
	bool isCanRender;
	bool isDoor;

	int aniId;

	CSimon* simon;
public:
	ChangeSceneObjects()
	{
		simon = CSimon::getInstance();
		simonAutoGoDistance = 0;
		simonAutoGo = false;
		isDoor = false;
		this->AddAnimation(ANI_DOOR_OPNEN);
		this->AddAnimation(ANI_DOOR_CLOSE);
		camAutoGo = false;
		isCanRender = true;
		aniId = 0;
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