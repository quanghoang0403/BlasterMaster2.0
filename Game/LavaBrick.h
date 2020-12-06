#pragma once
#include "Enemy.h"


class LavaBrick : public Enemy
{
public: 
	int frameH, frameW;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* objects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Activation();
	virtual bool IsContain(RECT rect1, RECT rect2);
	virtual float GetDistance(D3DXVECTOR2 pos, D3DXVECTOR2 target);
	virtual void GetCenterBoundingBox(float& x, float& y);
	LavaBrick(float fWidth, float fHeight);
	~LavaBrick();
};