#pragma once
#include "Enemy.h"
#include <ctime>
#include "Timer.h"
#include "Camera.h"
#include "BossHand.h"

#define BOSS_SPEED_VX									0.017f
#define BOSS_SPEED_VY									0.017f

#define BOSS_BBOX_WIDTH									60
#define BOSS_BBOX_HEIGHT								65
#define BOSS_BBOX_HEIGHT_DIE							9

#define BOSS_STATE_FLY									100
#define BOSS_STATE_ATTACK								200
#define BOSS_STATE_DIE									300

#define BOSS_ANI_FLY									0
#define BOSS_ANI_ATTACK									1
#define BOSS_ANI_DIE									2

#define BOSS_MAXHEALTH									2

class Boss: public Enemy
{
	float tempX, tempY;

	Timer* TimeDelayX = new Timer(300);
	Timer* TimeDelayY = new Timer(300);
	RECT PosBoss;
	vector<BossHand*> ListHand;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

public:
	Boss(float x, float y, LPGAMEENTITY t);
	virtual void SetState(int state);
	virtual void Activation();

};

