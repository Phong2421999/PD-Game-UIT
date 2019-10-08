#include "CTile.h"

CTile::CTile(int x, int y, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex) {
	this->x = x;
	this->y = y;
	this->top = top;
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void CTile::Draw()
{
	CGame::GetInstance()->Draw(x, y, texture, left, top, right, bottom);
}


CTile::~CTile()
{
}