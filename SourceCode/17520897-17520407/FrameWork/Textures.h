#pragma once
#include <unordered_map>
#include <d3dx9.h>

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures * __instance;
	unordered_map<int, LPDIRECT3DTEXTURE9> textures; //Giống từ điển (key-value) 
	//Mỗi textures nạp lên đều có mã số
	//Vị trí nào cũng được 

public: 
	CTextures();

	void Add(int id, LPCSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	static CTextures * GetInstance();
};