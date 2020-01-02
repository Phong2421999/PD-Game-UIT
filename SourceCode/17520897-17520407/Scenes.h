#pragma once
#include "Scene.h"
#include <unordered_map>


using namespace std;

struct SceneData
{
	int sceneId;
	int resetSceneId;
	int defaultSimonStartX, defaultSimonStartY;
	int simonNx;
};

class Scenes {
private:
	static Scenes* __instance;
	unordered_map <int, LPSCENE> scenes;
	unordered_map <int, SceneData> sceneData;
	float simonStartPosX, simonStartPosY;
	int simonDefaultNx;
	bool isLoadBlackScene;
	DWORD timeLoadBlackScene;
public:
	void Add(int id, LPSCENE scene)
	{
		scenes[id] = scene;
	}
	void AddSceneData(int sceneId, int resetSceneId, int defaultSimonX, int defaultSimonY, int simonNx)
	{
		SceneData temp;
		temp.defaultSimonStartX = defaultSimonX;
		temp.defaultSimonStartY = defaultSimonY;
		temp.sceneId = sceneId;
		temp.resetSceneId = resetSceneId;
		temp.simonNx = simonNx;
		sceneData[sceneId] = temp;
	}
	void SetSimonStartPos(float x, float y)
	{
		this->simonStartPosX = x;
		this->simonStartPosY = y;
	}
	void SetLoadBlackScene(bool b)
	{
		this->isLoadBlackScene = b;
	}
	void SetTimeLoadBlackScene(DWORD timeLoadBlackScene)
	{
		this->timeLoadBlackScene = timeLoadBlackScene;
	}
	void GetSimonStartPos(float &x, float &y)
	{
		x = this->simonStartPosX;
		y = this->simonStartPosY;
	}
	void GetSimonDefaultPos(int sceneId, float &x, float &y)
	{
		SceneData data = sceneData[sceneId];
		x = data.defaultSimonStartX;
		y = data.defaultSimonStartY;
	}
	void GetSimonDefaultNX(int sceneId, int &nx)
	{
		SceneData data = sceneData[sceneId];
		nx = data.simonNx;
	}
	bool GetLoadBlackScene()
	{
		return isLoadBlackScene;
	}
	DWORD GetTimeLoadBlackScene()
	{
		return timeLoadBlackScene;
	}
	int GetSimonNx()
	{
		return simonDefaultNx;
	}
	void ResetScene(int currentSceneId)
	{
		int id = sceneData[currentSceneId].sceneId;
		int resetSceneId = sceneData[currentSceneId].resetSceneId;


		if (id != resetSceneId)
		{
			scenes[id]->Reset();
			scenes[resetSceneId]->Reset();
			//scenes[resetSceneId]->StartLoadScene();
		}
		else
		{
			scenes[resetSceneId]->Reset();
			//scenes[resetSceneId]->StartLoadScene();
		}
		CSimon::getInstance()->setSceneId(resetSceneId);
	}
	LPSCENE Get(int id)
	{
		return scenes[id];
	}
	void NextScenes()
	{
		int curScene = CSimon::getInstance()->getCurrentScene();
		float defaultX, defaultY;
		int nx;
		GetSimonDefaultPos(curScene + 1, defaultX, defaultY);
		GetSimonDefaultNX(curScene + 1, nx);
		CSimon::getInstance()->setSceneId(curScene + 1);
		simonDefaultNx = nx;
		SetSimonStartPos(defaultX, defaultY);
		DebugOut(L"\ndefau;tX: %f, defaultY: %f", defaultX, defaultY);
	}
	static  Scenes* GetInstance();
};