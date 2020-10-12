#include "MainJasonBullet.h"

MainJasonBullet::MainJasonBullet()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_SMALL_JASON_BULLET));
	x = 0;
	y = 0;
	alpha = 0;
	isCollisionBrick = 0;
	isCollisionEnemies = 0;
	isDone = true;
	timeDelayed = 0;
	timeDelayMax = SMALL_JASON_BULLET_DELAY;
}

MainJasonBullet::~MainJasonBullet() {}

void MainJasonBullet::Update(DWORD dt, vector<LPGAMEENTITY>* colliable_objects)
{
	if (isDone == true)
	{
		alpha = 0;
	}
	else
	{
		timeDelayed += dt;
		Entity::Update(dt);
		if (isTargetTop == false) {
			vx = BULLET_SPEED * direction;
			vy = 0;
		}
		else {
			vy = -BULLET_SPEED;
			vx = 0;
		}
#pragma region Xử lý va chạm
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(colliable_objects, coEvents);

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

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (e->obj->GetType() == EntityType::BRICK)
				{
						isCollisionBrick = 1;
						x += min_tx * dx + nx * 0.4f;
						y += min_ty * dy + ny * 0.4f;
						vx = 0;
						vy = 0;
				}
				if (e->obj->GetType() == EntityType::GOLEM)
				{
					isCollisionEnemies = 1;
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;
					vx = 0;
					vy = 0;
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion
	}
}

void MainJasonBullet::Render()
{
	RenderBoundingBox();
	int ani;
	if (timeDelayed >= timeDelayMax)
	{
		isDone = true;
		timeDelayed = 0;
	}
	else
	{
		if (isCollisionBrick == 0 && isCollisionEnemies == 0)
		{
			if (isTargetTop == true)
			{
				ani = SMALL_BULLET_JASON_ANI_TOP;
				animationSet->at(ani)->OldRender(x, y, alpha);
			}
			else
			{
				ani = SMALL_BULLET_JASON_ANI_RIGHT;
				animationSet->at(ani)->Render(direction, x, y, alpha);
			}
		}
		else if (isCollisionEnemies == 1)
		{
			isDone = true;
			timeDelayed = 0;;
		}
		else if (isCollisionBrick == 1)
		{
			ani = SMALL_BULLET_JASON_BANG_ANI;
			animationSet->at(ani)->OldRender(x, y - DISTANCE_TO_BANG, alpha);
			if (animationSet->at(ani)->GetFrame() == 2)
			{
				isDone = true;
				timeDelayed = 0;
			}
		}
	}
}

void MainJasonBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	if (isTargetTop == false)
	{
		r = x + SMALL_BULLET_BBOX_WIDTH;
		b = y + SMALL_BULLET_BBOX_HEIGHT;
	}
	else
	{
		r = x + SMALL_BULLET_BBOX_HEIGHT;
		b = y + SMALL_BULLET_BBOX_WIDTH;
	}
}