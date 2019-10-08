#include "CTiles.h"


CTiles::CTiles(LPCSTR filePath, int texId)
{
	HRESULT result = D3DXGetImageInfoFromFileA(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	tex = CTextures::GetInstance()->Get(texId);
}

void CTiles::SetMapPosition(int x, int y) {
	this->offsetX = x;
	this->offsetY = y;
}

void CTiles::LoadMap() {
	DebugOut(L"[INFO]Tiles Width: %d\n", info.Height);

	for (int i = 0; i <= (info.Height % 32) -1; i++)
	{
		for (int j = 0; j <= (info.Width % 32) - 1; j++)
		{

			int left = i * 32;
			int top = j * 32;
			int right = left + 32;
			int bottom = top + 32;
			int x = left + offsetX;
			int y = top + offsetY;
			LPTILE tile = new CTile(x, y, left, top, right, bottom, tex);
			tiles.push_back(tile);
		}

	}

}

void CTiles::Draw()
{
	DebugOut(L"[INFO]Tiles Size: %d\n", tiles.size());
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i]->Draw();
	}
}