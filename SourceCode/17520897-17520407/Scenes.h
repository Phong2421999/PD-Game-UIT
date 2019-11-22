#pragma once
#include "Scene.h"
#include <unordered_map>


using namespace std;

struct SceneData
{
	int sceneId;
	int resetSceneId;
};

class Scenes {
private:
	static Scenes* __instance;
	unordered_map <int, LPSCENE> scenes;
	unordered_map <int, SceneData> sceneData;
public:
	void Add(int id, LPSCENE scene)
	{
		scenes[id] = scene;
	}
	void AddSceneData(int sceneId, int resetSceneId)
	{
		SceneData temp;
		temp.sceneId = sceneId;
		temp.resetSceneId = resetSceneId;
		sceneData[sceneId] = temp;
	}
	void ResetScene(int currentSceneId)
	{
		int id = sceneData[currentSceneId].sceneId;
		int resetSceneId = sceneData[currentSceneId].resetSceneId;


		if (id != resetSceneId)
		{
			scenes[id]->Reset();
			scenes[resetSceneId]->Reset();
			scenes[resetSceneId]->StartLoadScene();
		}
		else
		{
			scenes[resetSceneId]->Reset();
			scenes[resetSceneId]->StartLoadScene();
		}
	}
	LPSCENE Get(int id)
	{
		return scenes[id];
	}
	static  Scenes* GetInstance();
};