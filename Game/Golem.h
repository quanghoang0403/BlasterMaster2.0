#pragma once
#include "Entity.h"
#include "Brick.h"

#define GOLEM_WALKING_SPEED 0.18f;

#define GOLEM_GRAVITY	0.002f

#define GOLEM_BBOX_WIDTH 12
#define GOLEM_BBOX_HEIGHT 21
#define GOLEM_BBOX_HEIGHT_DIE 9

#define GOLEM_DISTANCE_MIN		64
#define GOLEM_DISTANCE_MAX		110

#define GOLEM_STATE_WALKING 100
#define GOLEM_STATE_DIE 200

#define GOLEM_ANI_WALKING 0
#define GOLEM_ANI_DIE 1

class Golem: public Entity
{
	
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();
	

public:
	Golem();
	virtual void SetState(int state);
};

