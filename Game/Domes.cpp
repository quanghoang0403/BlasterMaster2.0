#include "Domes.h"
#include "Brick.h"

void Domes::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DOMES_BBOX_WIDTH;
	bottom = y + DOMES_BBOX_HEIGHT;
}

void Domes::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	Entity::Update(dt);

	if (dgravity == 1)
	{
		vy -= DOMES_GRAVITY;
		SetState(DOMES_STATE_WALKING_TOP_BOTTOM_RIGHT);
	}
	else if (dgravity == 2)
	{
		vx += DOMES_GRAVITY;
		SetState(DOMES_STATE_WALKING_LEFT_RIGHT_BOTTOM);
	}
	else if (dgravity == 3)
	{
		vy += DOMES_GRAVITY;
		SetState(DOMES_STATE_WALKING_TOP_BOTTOM_LEFT);
	}
	else if (dgravity == 4)
	{
		vx -= DOMES_GRAVITY;
		SetState(DOMES_STATE_WALKING_LEFT_RIGHT_TOP);
	}

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
	if (state != DOMES_STATE_DIE)
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
		float min_tx, min_ty, nx=0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		
		DebugOut(L"\nnx:  %f", nx);
		DebugOut(L"\nny:  %f", ny);
		if (this->dgravity == 3)
		{
			
			if (nx!=0)
			{
				if (vx < 0 && nx == 1)
					this->dgravity = 4;

				else
					this->dgravity = 2;
			}
		}
		else if (this->dgravity == 4)
		{
			if (ny == -1)
			{
				SetState(DOMES_STATE_WALKING_LEFT_RIGHT_TOP);
				//vx = 0;
			}
			if (ny == 1)
			{
				if (ny == 1 && this->vx < 0)
					this->dgravity = 1;
				else
					this->dgravity = 3;
			}
		}
		else if (this->dgravity == 1)
		{
			
			if (nx!=0)
			{
				if (this->vx > 0 && nx == -1)
				{					
					this->dgravity = 2;
					
				}
												
			}
			else if (nx==0)
			{
				for (int i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult.at(i);
					if (dynamic_cast<Brick*>(e->obj))
					{
						Brick* brick = dynamic_cast<Brick*>(e->obj);

						if (x + 0.4f > (brick->frameW + brick->x))
						{
							this->dgravity = 4;
						}
					}
				}
			}
			
		}
		else if (this->dgravity == 2)
		{
			if (vy>0)
			{
				for (int i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult.at(i);
					if (dynamic_cast<Brick*>(e->obj)) 
					{
						Brick* brick = dynamic_cast<Brick*>(e->obj);
												
						if (y >= (brick->frameH+brick->y))
						{
							this->dgravity = 1;
							
						}
					}
				}
			}
			
		}

		//DebugOut(L"\ndgravity:  %d", this->dgravity);

		//DebugOut(L"\nvx:  %f", this->vx);
		//DebugOut(L"\nvy:  %f", this->vy);
		//DebugOut(L"\nvy:  %d", vy);
		
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Domes::Render()
{
	int ani;

	if (dgravity == 1 || dgravity == 3)
	{
		if (vx > 0)
		{
			ani = DOMES_ANI_WALKING_TOP_BOTTOM_RIGHT;
			animationSet->at(ani)->RenderTopBottom(1, x, y);
		}
		else
		{
			ani = DOMES_ANI_WALKING_TOP_BOTTOM_LEFT;
			animationSet->at(ani)->RenderTopBottom(-1, x, y);
		}
	}
	else
	{
		if (vy > 0)
		{
			ani = DOMES_ANI_WALKING_LEFT_RIGHT_BOTTOM;
			animationSet->at(ani)->Render(1, x, y);
		}
		else
		{
			ani = DOMES_ANI_WALKING_LEFT_RIGHT_TOP;
			animationSet->at(ani)->Render(-1, x, y);
		}
	}
	
	RenderBoundingBox();
}

Domes::Domes(float x, float y, LPGAMEENTITY t)
{
	SetState(DOMES_STATE_WALKING_TOP_BOTTOM_RIGHT);
	tag = EntityType::DOMES;
	this->x = x;
	this->y = y;
	this->dgravity = 4;
	nx = -1;
	this->target = t;
	health = DOMES_MAXHEALTH;
	isActive = false;
}

void Domes::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case DOMES_STATE_DIE:
		y += DOMES_BBOX_HEIGHT - DOMES_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case DOMES_STATE_WALKING_TOP_BOTTOM_RIGHT:
		vx = DOMES_WALKING_SPEED;
		break;
	case DOMES_STATE_WALKING_TOP_BOTTOM_LEFT:
		vx = -DOMES_WALKING_SPEED;
		break;
	case DOMES_STATE_WALKING_LEFT_RIGHT_TOP:
		vy = -DOMES_WALKING_SPEED;
		break;
	case DOMES_STATE_WALKING_LEFT_RIGHT_BOTTOM:
		vy = DOMES_WALKING_SPEED;
		break;

	}
}
