
#pragma once
#include "Enemy.h"

#define INSECT_WALKING_SPEED		0.018f;

#define INSECT_GRAVITY				0.002f

#define INSECT_BBOX_WIDTH			26
#define INSECT_BBOX_HEIGHT			21
#define INSECT_BBOX_HEIGHT_DIE		9

#define INSECT_STATE_FLY			100
#define INSECT_STATE_DIE			200

#define INSECT_ANI_FLY				0
#define INSECT_ANI_DIE				1

#define INSECT_MAXHEALTH			1

class Insect: public Enemy
{


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();


public:
	Insect(float x, float y, LPGAMEENTITY t);
	virtual void SetState(int state);
	virtual void Activation();
};

