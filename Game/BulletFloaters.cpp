#include "BulletFloaters.h"
#include <algorithm>

BulletFloaters::BulletFloaters(float _x, float _y, float _posRight, float _posBottom, float _postargetLeft, float _postargetTop, float _postargetRight, float _postargetBottom)
{
	tag = BULLETENEMY = BULLETFLOATERS;
	
	isFinish = false;
	posRight = _posRight;
	posBottom = _posBottom;
	postargetLeft = _postargetLeft; 
	postargetTop = _postargetTop; 
	postargetRight = _postargetRight;
	postargetBottom = _postargetBottom;
	_isFinish = 0;
	aniBullet = CAnimations::GetInstance()->Get(BULLET_LOATERS_ANI_FLY);
	RenderSpeedFollowTarget(_x, _y);
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

void BulletFloaters::SetCenterBoundingBox(float& x, float& y, float _posLeft, float _posTop, float _posRight, float _posBottom)
{
	x = (_posLeft + _posRight) / 2;
	y = (_posTop + _posBottom) / 2;
}

void BulletFloaters::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt);
	
	if (!_isFinish)
	{
		vx = RenderVx;
		vy = RenderVy;
	}
	else
	{
		vx = 0;
		vy = 0;
	}
		

#pragma region Xử lý tiền va chạm
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> collision;

	coEvents.clear();
	collision.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == EntityType::BRICK || coObjects->at(i)->GetType() == EntityType::PLAYER)
			collision.push_back(coObjects->at(i));

	// turn off collision when die 
	CalcPotentialCollisions(&collision, coEvents);

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
						
		if (!nx || !ny)
			_isFinish = 1;
							
	}
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void BulletFloaters::RenderSpeedFollowTarget(float _x, float _y)
{
	SetCenterBoundingBox(x, y, _x, _y, posRight, posBottom);
	posBullet = D3DXVECTOR2(x, y);
	focus = CreatePosFollowTarget(D3DXVECTOR2((postargetLeft + postargetRight) / 2, (postargetTop + postargetBottom) / 2), posBullet);
	posBullet = RadialMovement(focus, posBullet, LOATERS_BULLET_SPEED);
	RenderVx = posBullet.x/14;
	RenderVy = posBullet.y/14;
}


void BulletFloaters::Render()
{
	if (_isFinish)
	{
		aniBullet = CAnimations::GetInstance()->Get(BULLET_LOATERS_ANI_BANG);
		RenderBoundingBox();
		aniBullet->OldRender(x, y);
		if (CAnimations::GetInstance()->Get(BULLET_LOATERS_ANI_BANG)->GetFrame() == 3) //Luc nay no bang 3 hoai, phai cho no bang 0 tip
		{
			isFinish = 1;
			return;
		}
	}
	else
	{
		aniBullet = CAnimations::GetInstance()->Get(BULLET_LOATERS_ANI_FLY);
		RenderBoundingBox();
		aniBullet->OldRender(x, y);
	}
		
		
	
	
}
