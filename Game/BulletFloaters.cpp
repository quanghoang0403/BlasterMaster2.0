#include "BulletFloaters.h"
#include <algorithm>

BulletFloaters::BulletFloaters(float _x, float _y, float _postargetX, float _postargetY)
{
	
	tag = BULLETENEMY = BULLETFLOATERS;
	isFinish = false;
	postargetX = _postargetX;
	postargetY = _postargetY;
	isStart = 0;
	aniBullet = CAnimations::GetInstance()->Get(BULLET_LOATERS_ANI);
	posBullet = D3DXVECTOR2(_x, _y);
	focus = CreatePosFollowTarget(D3DXVECTOR2(postargetX, postargetY), posBullet);
}

void BulletFloaters::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;
}

int BulletFloaters::GetDamage()
{
	return LOATERS_BULLET_DAMAGE;
}

bool BulletFloaters::IsStart()
{
	return isStart;
}

void BulletFloaters::Start(float _x, float _y)
{
	isStart = 1;
	x = _x;
	y = _y;
}

void BulletFloaters::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt);
			
	if (!isFinish)
	{
		posBullet += RadialMovement(focus, posBullet, LOATERS_BULLET_SPEED);
		x = posBullet.x;
		y = posBullet.y;
	}
	
	if (isFinish) { vx = 0; vy = 0; return; }
	
#pragma region Xử lý tiền va chạm
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> bricks;

	coEvents.clear();
	bricks.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == EntityType::BRICK)
			bricks.push_back(coObjects->at(i));

	// turn off collision when die 
	CalcPotentialCollisions(&bricks, coEvents);

#pragma endregion


#pragma region Xử lý logic khi va chạm
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		isFinish = 1;
	}

	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
	
}






void BulletFloaters::Render()
{
	RenderBoundingBox();
	aniBullet->OldRender(x, y);
}
