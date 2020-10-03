#pragma once
#include "Entity.h"

#define CENTIPEDE_WALKING_SPEED 0.05f;

#define CENTIPEDE_BBOX_WIDTH 17
#define CENTIPEDE_BBOX_HEIGHT 9
#define CENTIPEDE_BBOX_HEIGHT_DIE 9

#define CENTIPEDE_STATE_WALKING 100
#define CENTIPEDE_STATE_DIE 200

#define CENTIPEDE_ANI_WALKING 0
#define CENTIPEDE_ANI_DIE 1

class Centipede : public Entity
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

public:
	Centipede();
	virtual void SetState(int state);
};