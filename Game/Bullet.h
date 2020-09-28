#pragma once
#include "Entity.h"

#define BIG_BULLET_BBOX_WIDTH			22
#define BIG_BULLET_BBOX_HEIGHT			6

#define SMALLSOPHIA_BULLET_BBOX_WIDTH	4
#define SMALLSOPHIA_BULLET_BBOX_HEIGHT	4

#define ELECTRIC_BULLET_JASON_BBOX_WIDTH	14
#define ELECTRIC_BULLET_JASON_BBOX_HEIGHT	16

#define SMALL_BULLET_JASON_ANI_RIGHT	0
#define SMALL_BULLET_JASON_ANI_TOP		1
#define BIG_BULLET_JASON_ANI_RIGHT		2
#define BIG_BULLET_JASON_ANI_TOP		3
#define BANG_ANI						4
#define ELECTRIC_BULLET_ANI_JASON		5
#define SMALL_BULLET_ANI_SOPHIA			6



class Bullet : public Entity
{
	bool isDone;
	/*bool isReceivedPos;
	float timeDelayed, timeDelayMax;*/
	float timeDelayed;
	int damage;

public:
	Bullet();
	~Bullet();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

	void ResetDelay() { timeDelayed = 0; }
	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }
	int GetDamage() { return damage; }

};