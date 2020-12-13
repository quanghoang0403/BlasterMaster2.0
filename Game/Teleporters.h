#pragma once
#include "Enemy.h"
#include "Timer.h"
#include <ctime>
#include "Camera.h"

#define TELEPORTERS_BBOX_WIDTH							18
#define TELEPORTERS_BBOX_HEIGHT							15
#define TELEPORTERS_BBOX_HEIGHT_DIE						9

#define TELEPORTERS_STATE_ATTACK						400
#define TELEPORTERS_STATE_DIE							500

#define TELEPORTERS_ANI_ATTACK							1
#define TELEPORTERS_ANI_DIE								2


#define EYEBALLS_MAXHEALTH								2

class Teleporters : public Enemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

public:
	Teleporters(float x, float y, LPGAMEENTITY t);
	virtual void SetState(int state);
	virtual void Activation();
	void Attack();
};

