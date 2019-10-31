#include "CFont.h"


CFont::CFont(int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex) {
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->tex = tex;
}

void CFont::Draw(float x, float y) {
	CGame::GetInstance()->Draw(x, y, tex, left, top, right, bottom);
}