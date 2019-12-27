#pragma once
#include "Scene.h"
#include <unordered_map>


using namespace std;

struct SceneData
{
	int sceneId;
	int resetSceneId;
	int defaultSimonStartX, defaultSimonStartY;
};

class Scenes {
private:
	static Scenes* __instance;
	unordered_map <int, LPSCENE> scenes;
	unordered_map <int, SceneData> sceneData;
	float simonStartPosX, simonStartPosY;
	bool isLoadBlackScene;
	DWORD timeLoadBlackScene;
public:
	void Add(int id, LPSCENE scene)
	{
		scenes[id] = scene;
	}
	void AddSceneData(int sceneId, int resetSceneId, int defaultSimonX, int defaultSimonY)
	{
		SceneData temp;
		temp.defaultSimonStartX = defaultSimonX;
		temp.defaultSimonStartY = defaultSimonY;
		temp.sceneId = sceneId;
		temp.resetSceneId = resetSceneId;
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
	bool GetLoadBlackScene()
	{
		return isLoadBlackScene;
	}
	DWORD GetTimeLoadBlackScene()
	{
		return timeLoadBlackScene;
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
	static  Scenes* GetInstance();
};