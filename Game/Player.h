#pragma once
#include "Entity.h"
#include "Bullet.h"
#include <map>

#define SOPHIA_WALKING_SPEED_UNIT		0.0040f//0.010f
#define SOPHIA_WALKING_SPEED			0.1f 
#define SOPHIA_WALKING_SPEED_BONUS		0.003f//0.007f

#define SOPHIA_JUMP_SPEED_Y				0.223f
//#define SOPHIA_JUMP_SPEED_Y_BONUS		0.45f
#define SOPHIA_JUMP_DEFLECT_SPEED		0.10f
#define SOPHIA_GRAVITY					0.0004f
#define SOPHIA_DIE_DEFLECT_SPEED		0.5f

#define SOPHIA_JASON_HEIGHT_GUN_FLIP	15.5

#define SOPHIA_STATE_IDLE				0
#define SOPHIA_STATE_WALKING_RIGHT		100
#define SOPHIA_STATE_WALKING_LEFT		200
#define SOPHIA_STATE_JUMP				300
#define SOPHIA_STATE_DIE				400
#define SOPHIA_STATE_GUN_UNFLIP			500


#define SOPHIA_ANI_JASON_IDLE_RIGHT					0
#define SOPHIA_ANI_JASON_IDLE_LEFT					1

#define SOPHIA_ANI_JASON_WALKING_RIGHT				2
#define SOPHIA_ANI_JASON_WALKING_LEFT				3

#define SOPHIA_ANI_JASON_JUMP_UP_IDLE_RIGHT			4
#define SOPHIA_ANI_JASON_JUMP_UP_IDLE_LEFT			5
#define SOPHIA_ANI_JASON_JUMP_DOWN_IDLE_RIGHT		6
#define SOPHIA_ANI_JASON_JUMP_DOWN_IDLE_LEFT		7
#define SOPHIA_ANI_JASON_JUMP_UP_WALKING_RIGHT		8
#define SOPHIA_ANI_JASON_JUMP_UP_WALKING_LEFT		9
#define SOPHIA_ANI_JASON_JUMP_DOWN_WALKING_RIGHT	10
#define SOPHIA_ANI_JASON_JUMP_DOWN_WALKING_LEFT		11

#define SOPHIA_ANI_GUN_FLIP_RIGHT					12
#define SOPHIA_ANI_GUN_FLIP_LEFT					13

#define SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_1			14
#define SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_2			15
#define SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_3			16
#define SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_4			17

#define SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_1				18
#define SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_2				19
#define SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_3				20
#define SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_4				21

#define SOPHIA_JASON_ANI_DIE						22

#define SOPHIA_JASON_BBOX_WIDTH		26
#define SOPHIA_JASON_BBOX_HEIGHT	16.5

#define MARIO_UNTOUCHABLE_TIME 5000

#define HIGHT_LEVER1 43

class Player : public Entity
{
	int level;
	int untouchable;
	bool isJumping = false;
	bool isGunFlipping = false;
	bool isJumpHandle;
	DWORD untouchable_start;

	Bullet* mainBullet1;
	Bullet* mainBullet2;
	Bullet* mainBullet3;
	Bullet* supBullet;

	float start_x;			// initial position of Mario at scene
	float start_y;

	float backup_JumpY;
	bool isPressJump;
	bool isPressFlipGun;

public:
	Player(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY>* colliable_objects = NULL);
	virtual void Render();

	void SetDirection(int d) { direction = d; }
	void SetState(int state);
	void SetPressSpace() { isPressJump = 1; }
	void SetPressUp(bool a) { isPressFlipGun = a; }
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void GetPositionCenter(float& x, float& y) { x = this->x + SOPHIA_JASON_BBOX_WIDTH / 2; y = this->y + SOPHIA_JASON_BBOX_HEIGHT / 2; }
	bool isGunFlippingg() { return isGunFlipping; }
	void SetVx(float Vx) { vx = Vx; }
	void SetVy(float Vy) { vy = Vy; }
	float GetDy() { return dy; }
	float GetVy() { return vy; }
	void Reset();
	void GetInfoForBullet(int& direct, int& isTargetTop, float& playerPosX, float& playerPosY) { direct = direction; isTargetTop = isGunFlipping; playerPosX = x; playerPosY = y; }

	//Bullet* GetPlayerMainBullet() { return mainBullet; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};