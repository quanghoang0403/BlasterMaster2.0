#include "BossHand.h"

void BossHand::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (species == 1)
	{
		l = x;
		t = y;
		r = x + HAND_BBOX_WIDTH_BONES;
		b = y + HAND_BBOX_HEIGHT_BONES;
	}
	else
	{
		l = x;
		t = y;
		r = x + HAND_BBOX_WIDTH_CLAW;
		b = y + HAND_BBOX_HEIGHT_CLAW;
	}
	
}


BossHand::BossHand(float _x, float _y, int _species, int _direction)
{
	//SetCenterBoundingBox(x, y, _x, _y, _posRight, _posBottom);
	x = _x;
	y = _y;
	
	species = _species;
	if (species == 1)
	{
		aniBullet = CAnimations::GetInstance()->Get(HAND_BOSS_ANI_BONES);
		BonesLatest = 0;
		flag = 1;
	}
	else
	{
		isUp = 1;
		aniBullet = CAnimations::GetInstance()->Get(HAND_BOSS_ANI_CLAW);
		_state = 1;
		temp =1;
	}
	//TimeChangeDelay->Start();
	direct = _direction;
	
	SetBBARGB(0);

}

void BossHand::Render()
{

	aniBullet->Render(direct, x, y);
	RenderBoundingBox();
	
}

void BossHand::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
}

int BossHand::GetDamage()
{
	return 0;
}

void BossHand::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects, RECT _target, D3DXVECTOR2 Speed, D3DXVECTOR2 SpeedBoss, RECT posBoss)
{
	Entity::Update(dt);
	float _xBoss, _yBoss;
	SetCenterBoundingBox(_xTarget, _yTarget, _target.left, _target.top, _target.right, _target.bottom);
	SetCenterBoundingBox(_xBoss, _yBoss, posBoss.left, posBoss.top+5, posBoss.right, posBoss.bottom);

	if (species == 1)
	{
		
		SetCenterBoundingBox(_xHand, _yHand, x, y, x + HAND_BBOX_WIDTH_BONES, y + HAND_BBOX_HEIGHT_BONES);
		
		
		if (GetDistance(D3DXVECTOR2(_xHand, _yHand), D3DXVECTOR2(_xTarget, _yTarget)) >= 18 && flag)
		{
			
			vy = Speed.y;
			
			if (GetDistance(D3DXVECTOR2(_xHand, _yHand), D3DXVECTOR2(_xTarget, _yTarget)) >= 23 && flag)
			{
				vx = Speed.x;
				DebugOut(L"\nCheck: Trong   ");
									
			}
			else
			{
				if (_yHand > _yBoss)
				{
					vx = SpeedBoss.x;
				}
				else
				{
					vx = Speed.x;
				}
			}
			
				
		}
		else
		{
			vx = SpeedBoss.x;
			vy = SpeedBoss.y;
		
		}
				

		if (flag != 2)
		{
		
			if (vy < 0 && _yHand > _yBoss - 2 && _yHand < _yBoss + 2  && _yHand > _yBoss) // Dừng trục Y
			{
				flag = 0;
			}
			else if ( _xHand > _xBoss - 2 && _xHand < _xBoss + 2) // Dừng trục X
			{
				flag = 0;
			}
		}
			

		if (flag == 0 && flag != 2)
		{
			if (Speed.y < 0 && _yTarget < _yHand-5) // Start lúc thẳng hàng ở center Boss
				flag = 1;
			else if (Speed.y > 0 && Speed.x < 0) // Start lúc thẳng cột ở center Boss
			{
				flag = 1;
			}
			
		}
		
		
	
	}
	//Claw
	else
	{
		if (direct == -1)
		{
			SetCenterBoundingBox(_xHand, _yHand, x, y, x + HAND_BBOX_WIDTH_CLAW, y + HAND_BBOX_HEIGHT_CLAW);
			if (x == _target.left && y == _target.top)
			{
				RenderSpeedFollowTarget(0.5, _xTarget, _yTarget + 110);
				vx = Speed.x;
				vy = RenderVy * 2;
			}
			else if (_yHand >= _yTarget + 88 && _xHand > _xTarget - 100)
			{
				RenderSpeedFollowTarget(0.5, _xTarget - 130, _yTarget);
				vy = Speed.y;
				vx = RenderVx * 2;

			}
			else if (_xHand <= _xTarget - 95 && _yHand >= _yTarget - 50)
			{
				RenderSpeedFollowTarget(0.5, _xTarget, _yTarget - 65);
				vx = Speed.x;
				vy = RenderVy * 3;
				//flag = 0;

			}
			else if (_yHand < _yTarget - 55 && _xHand < _xTarget)
			{
				RenderSpeedFollowTarget(0.5, _xTarget, _yTarget + 10);
				vx = RenderVx * 3;
				vy = RenderVy * 3;

			}
			else if (_xHand > _xTarget)
			{
				RenderSpeedFollowTarget(0.5, _xTarget - 150, _yTarget + 120);
				vx = RenderVx * 3;
				vy = RenderVy * 3;
			}
		}
		else
		{
			SetCenterBoundingBox(_xHand, _yHand, x, y, x + HAND_BBOX_WIDTH_CLAW, y + HAND_BBOX_HEIGHT_CLAW);
			if (x == _target.right - 18 && y == _target.top)
			{
				RenderSpeedFollowTarget(0.5, _xTarget, _yTarget + 110);
				vx = Speed.x;
				vy = RenderVy * 4;
			}
			else if (_yHand >= _yTarget + 88 && _xHand < _xTarget + 90)
			{
				RenderSpeedFollowTarget(0.5, _xTarget + 150, _yTarget);
				vy = Speed.y;
				vx = RenderVx * 4;

			}
			else if (_xHand >= _xTarget + 80 && _yHand >= _yTarget + 50)
			{
				RenderSpeedFollowTarget(0.5, _xTarget + 130, _yTarget - 65);
				vx = Speed.x;
				vy = RenderVy * 6;
				//flag = 0;

			}
			else if (_yHand < _yTarget - 55 && _xHand > _xTarget)
			{
				RenderSpeedFollowTarget(0.5, _xTarget, _yTarget + 10);
				vx = RenderVx * 6;
				vy = RenderVy * 6;

			}
			else if (_xHand < _xTarget)
			{
				RenderSpeedFollowTarget(0.5, _xTarget + 120, _yTarget + 120);
				vx = RenderVx * 6;
				vy = RenderVy * 6;
			}
		}
		

	}
	

#pragma region Xử lý tiền va chạm
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> bricks;

	coEvents.clear();
	bricks.clear();
	/*for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == EntityType::BRICK)
			bricks.push_back(coObjects->at(i));*/

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
		y += min_ty * dy + ny * 0.004f;

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion

}

void BossHand::SetState(int state)
{
	Entity::SetState(state);



}

void BossHand::RenderSpeedFollowTarget(float _posLeft, float _posTop, float _posRight,
	float _posBottom, float _postargetLeft, float _postargetRight, float _postargetTop, float _postargetBottom, 
	float _BULLET_SPEED)
{
	
	SetCenterBoundingBox(x, y, _posLeft, _posTop, _posRight, _posBottom);
	posBullet = D3DXVECTOR2(x, y);
	focus = CreatePosFollowTarget(D3DXVECTOR2((_postargetLeft + _postargetRight) / 2, (_postargetTop + _postargetBottom) / 2), posBullet);
	posBullet = RadialMovement(focus, posBullet, _BULLET_SPEED);
	RenderVx = posBullet.x / 14;
	RenderVy = posBullet.y / 14;
}

void BossHand::SetCenterBoundingBox(float& x, float& y, float _posLeft, float _posTop, float _posRight, float _posBottom)
{
	/*if (_posBottom == (this->y + HAND_BBOX_HEIGHT_CLAW))
		_posBottom = this->y + 17;*/
	x = (_posLeft + _posRight) / 2;
	y = (_posTop + _posBottom) / 2;
}

int BossHand::GetSpecies()
{
	return species;
}

void BossHand::RenderSpeedFollowTarget(float _BULLET_SPEED, float _x, float _y)
{
	SetCenterBoundingBox(_xHand, _yHand, x, y, x + HAND_BBOX_WIDTH_CLAW, y + HAND_BBOX_HEIGHT_CLAW);
	D3DXVECTOR2 posHand;
	posHand = D3DXVECTOR2(_xHand, _yHand);
	focus = CreatePosFollowTarget(D3DXVECTOR2(_x, _y), posHand);
	posHand = RadialMovement(focus, posHand, _BULLET_SPEED);
	RenderVx = posHand.x / 14;
	RenderVy = posHand.y / 14;
}

int BossHand::GetDirect()
{
	return direct;
}

RECT BossHand::GetPos()
{
	RECT temp;
	if (species == 2)
	{
		temp.left = x;
		temp.top = y;
		temp.right = x + HAND_BBOX_WIDTH_CLAW;
		temp.bottom = y + HAND_BBOX_HEIGHT_CLAW;
	}
	else
	{

		temp.left = x;
		temp.top = y;
		temp.right = x + HAND_BBOX_WIDTH_BONES;
		temp.bottom = y + HAND_BBOX_HEIGHT_BONES;

	}
	return temp;
}

void BossHand::SetSpeed(float _vx, float _vy)
{
	vx = _vx;
	vy = _vy;
}

void BossHand::SetPosition(float _x, float _y)
{
	x = _x;
	y = _y;
}

void BossHand::DelayTime()
{
	if (TimeDelay->IsTimeUp())
	{
		TimeDelay->Reset();
		TimeDelay->Start();
	}

}

void BossHand::SetBonesLatest(bool _isBonesLatest)
{
	BonesLatest = _isBonesLatest;
}

D3DXVECTOR2 BossHand::GetSpeed()
{
	return D3DXVECTOR2(vx,vy);
}
