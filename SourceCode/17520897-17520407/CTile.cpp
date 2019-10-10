#include "CTile.h"

CTile::CTile(int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex) {
	this->top = top;
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void CTile::Draw(int x, int y)
{
	CGame::GetInstance()->Draw(x, y, texture, left, top, right, bottom);
}


CTile::~CTile()
{
}