#pragma once
#include "Scene.h"
#include <unordered_map>

class Scenes {
private:
	unordered_map <int, LPSCENE> scenes;
public:
	void Add(int id, LPSCENE scene)
	{
		scenes[id] = scene;
	}
	LPSCENE Get(int id)
	{
		return scenes[id];
	}
};