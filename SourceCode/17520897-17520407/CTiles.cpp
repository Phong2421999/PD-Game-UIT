#include "CTiles.h"


CTiles::CTiles(int texId, LPCSTR filePath)
{
	HRESULT result = D3DXGetImageInfoFromFileA(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	tex = CTextures::GetInstance()->Get(texId);
}

void CTiles::ReadMapTXT(LPCSTR filePath)
{
	ifstream inp(filePath, ios::in);
	inp >> RowMap >> ColumnMap >> RowTileSet >> ColumnTileSet >> frameWidth >> frameHeight >> DrawPositionX >> DrawPositionY;
	for (int i = 0; i < RowMap; i++)
		for (int j = 0; j < ColumnMap; j++)
		{
			inp >> TileMap[i][j];
		}
	inp.close();
}


void CTiles::LoadTile() {

	for (int i = 0; i < RowTileSet; i++)
	{
		for (int j = 0; j < ColumnTileSet; j++)
		{
			int left = j * frameWidth;
			int top = i * frameHeight;
			int right = left + frameWidth;
			int bottom = top + frameHeight;
			LPTILE tile = new CTile(left, top, right, bottom, tex);
			tiles.push_back(tile);
		}
	}
}

void CTiles::Render() {
	float cx = CGame::GetInstance()->GetCamPos_x();
	int beginColumn = cx / frameWidth;
	int endColumn = (cx + SCREEN_WIDTH) / frameWidth + 1;
	for (int i = 0; i < RowMap; i++) {
		for (int j = beginColumn; j < endColumn; j++) {
			tiles[TileMap[i][j]]->Draw(j*frameWidth + DrawPositionX, i*frameHeight + DrawPositionY);
		}
	}
};