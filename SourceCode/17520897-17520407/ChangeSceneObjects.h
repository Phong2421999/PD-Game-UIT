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

	int simonNx;
	int aniId;

	CSimon* simon;

	float simonStartPosX, simonStartPosY;
	bool isLoadBlackScene;
	DWORD timeLoadBlackScene;
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
		simonStartPosX = 0;
		simonStartPosY = 0;
		isLoadBlackScene = false;
		timeLoadBlackScene = 0;
		simonNx = 1;
	}
	void SetLoadBlackScene(bool b)
	{
		this->isLoadBlackScene = b;
	}
	void SetTimeLoadBlackScene(DWORD time)
	{
		this->timeLoadBlackScene = time;
	}
	void SetSimonStartPos(float x, float y)
	{
		simonStartPosX = x;
		simonStartPosY = y;
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
	void SetSimonNx(int nx)
	{
		this->simonNx = nx;
	}
	bool GetLoadBlackScene()
	{
		return isLoadBlackScene;
	}
	DWORD GetTimeLoadBlackScene()
	{
		return timeLoadBlackScene;
	}
	void GetSimonStartPos(float &x, float &y)
	{
		x = this->simonStartPosX;
		y = this->simonStartPosY;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
};