#pragma once
#include "Entity.h"

#define DOMES_WALKING_SPEED			0.05f;
#define DOMES_GRAVITY				0.002f

#define DOMES_BBOX_WIDTH			17
#define DOMES_BBOX_HEIGHT			6
#define DOMES_BBOX_HEIGHT_DIE		9

#define DOMES_STATE_WALKING			100
#define DOMES_STATE_DIE				200

#define DOMES_ANI_WALKING			0
#define DOMES_ANI_DIE				1

class Domes : public Entity
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

public:
	Domes();
	virtual void SetState(int state);
};

