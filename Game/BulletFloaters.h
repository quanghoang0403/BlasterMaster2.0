#pragma once
#include "BulletEnemy.h"
#include "Player.h"

#define BULLET_SPEED					0.05f;


#define BULLET_BBOX_WIDTH				4
#define BULLET_BBOX_HEIGHT				4

#define BULLET_LOATERS_ANI				900

#define LOATERS_BULLET_SPEED			2

#define LOATERS_BULLET_GRAVITY			0.001f

#define LOATERS_BULLET_VFLY				0.4f

#define LOATERS_BULLET_DELAY			500

#define LOATERS_BULLET_DAMAGE			1


class BulletFloaters: public BulletEnemy
{
	bool isStart;
	
	LPGAMEENTITY playerE = Player::GetInstance();
	int Xplayer, Yplayer;
	LPANIMATION aniBullet;
	float postargetX, postargetY;
public:
	BulletFloaters(float _x, float _y, float _postargetX, float _postargetY);
	~BulletFloaters();
	
	void Render();
	void Update(DWORD dt, vector<LPGAMEENTITY>* coObjects);

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetDamage();
	bool IsStart();
	void Start(float _x, float _y);
};

