#pragma once
#include "Scene.h"
#include <unordered_map>


using namespace std;

struct SceneData
{
	LPCSTR sceneGameObjectsPath;
	int mapId;
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
	void AddSceneData(int sceneId, int resetSceneId,int mapId, LPCSTR sceneGameObjectsPath)
	{
		SceneData temp;
		temp.mapId = mapId;
		temp.sceneGameObjectsPath = sceneGameObjectsPath;
		temp.sceneId = sceneId;
		temp.resetSceneId = resetSceneId;
		sceneData[sceneId] = temp;
	}
	void ResetScene(int currentSceneId)
	{
		int mapId = sceneData[currentSceneId].mapId;
		int id = sceneData[currentSceneId].sceneId;
		LPCSTR sceneGameObjectsPath = sceneData[currentSceneId].sceneGameObjectsPath;
		int resetSceneId = sceneData[currentSceneId].resetSceneId;

		int resetMapId = sceneData[resetSceneId].mapId;
		LPCSTR resetSceneGameObjectsPath = sceneData[resetSceneId].sceneGameObjectsPath;

		if (id != resetSceneId)
		{
			scenes[id]->clear();
			scenes[resetSceneId]->clear();
			scenes[id]->LoadSceneResource(mapId, sceneGameObjectsPath);
			scenes[resetSceneId]->LoadSceneResource(resetMapId, resetSceneGameObjectsPath);
			scenes[resetSceneId]->StartLoadScene();
		}
		else
		{
			scenes[resetSceneId]->clear();
			scenes[resetSceneId]->LoadSceneResource(resetMapId, resetSceneGameObjectsPath);
			scenes[resetSceneId]->StartLoadScene();
		}
	}
	LPSCENE Get(int id)
	{
		return scenes[id];
	}
	static  Scenes* GetInstance();
};