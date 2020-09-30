#pragma once
#include "Entity.h"

#define BIG_BULLET_BBOX_WIDTH			22
#define BIG_BULLET_BBOX_HEIGHT			6

#define SMALLSOPHIA_BULLET_BBOX_WIDTH	4
#define SMALLSOPHIA_BULLET_BBOX_HEIGHT	4

#define ELECTRIC_BULLET_JASON_BBOX_WIDTH	14
#define ELECTRIC_BULLET_JASON_BBOX_HEIGHT	16


#define BIG_BULLET_JASON_ANI_RIGHT		2
#define BIG_BULLET_JASON_ANI_TOP		3

#define ELECTRIC_BULLET_ANI_JASON		5
#define SMALL_BULLET_ANI_SOPHIA			6

#define DISTANCE_TO_GUN_WIDTH   9
#define DISTANCE_TO_GUN_HEIGHT  2
#define DISTANCE_TO_BANG		4

class Bullet;
typedef Bullet* LPBULLET;
class Bullet : public Entity
{
public:
	bool isDone;
	/*bool isReceivedPos;
	float timeDelayed, timeDelayMax;*/
	float timeDelayed;
	int damage;
	int isTargetTop;
	int alpha;
	int isCollision;

public:
	Bullet();
	~Bullet();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

	void Fire(int direct, int isGunFlip, float posX, float posY) { direction = direct; isTargetTop = isGunFlip; x = posX + DISTANCE_TO_GUN_WIDTH; y = posY + DISTANCE_TO_GUN_HEIGHT; alpha = 255; isDone = false; isCollision = 0; }
	void ResetDelay() { timeDelayed = 0; }
	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }
	int GetDamage() { return damage; }

};