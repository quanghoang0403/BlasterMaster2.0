#pragma once
#include "Entity.h"

#define SMALLSOPHIA_BULLET_BBOX_WIDTH	4
#define SMALLSOPHIA_BULLET_BBOX_HEIGHT	4

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
	int damage;
	int isTargetTop;
	int alpha;
	int isCollisionBrick;
	int isCollisionEnemies;
	float timeDelayed, timeDelayMax;

public:
	Bullet();
	~Bullet();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);
	virtual void Render();

	void Fire(int direct, int isGunFlip, float x, float y) {direction = direct; isTargetTop = isGunFlip; x = x + DISTANCE_TO_GUN_WIDTH; y = y + DISTANCE_TO_GUN_HEIGHT; alpha = 255; isDone = false; isCollisionBrick = 0; isCollisionEnemies = 0;}
	void ResetDelay() { timeDelayed = 0; }
	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }
	int GetDamage() { return damage; }

};