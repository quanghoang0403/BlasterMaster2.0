#pragma once
#include "Enemy.h"
#include "Timer.h"
#include <ctime>

// Chia trục tọa độ thành các phần x>0y>0 di chuyển giống x>0,y<0 (di chuyển ở dưới). X<0,y>0 di chuyển đi lên. CÒn X<0,Y<0 nữa dưới là di cchuyển ở dưới, còn nữa trên là di chuyển ở giữa.

#define EYEBALLS_BBOX_WIDTH								18
#define EYEBALLS_BBOX_HEIGHT							15
#define EYEBALLS_BBOX_HEIGHT_DIE						9

#define EYEBALLS_STATE_FLY								100
#define EYEBALLS_STATE_ATTACK							200
#define EYEBALLS_STATE_DIE								300

#define EYEBALLS_ANI_FLY								0
#define EYEBALLS_ANI_ATTACK								1
#define EYEBALLS_ANI_DIE								2

#define EYEBALLS_SITEACTIVE_PLAYER						150

#define EYEBALLS_MAXHEALTH								2

class Eyeballs:public Enemy
{

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

public:
	Eyeballs(float x, float y, LPGAMEENTITY t);

	virtual void SetState(int state);
	virtual void Activation();
	void Attack();

};

