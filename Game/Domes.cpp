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

#pragma region Xử lý Attack
	StartAttack();
#pragma endregion

#pragma region Xử lý State

	switch (directionclock)
	{
	case 1:
		if (isDamaged == true)
		{
			if (dgravity == 1 || dgravity == 3)
			{
				SetState(DOMES_STATE_ATTACK_TOP_BOTTOM);
				vx = 0;
			}
			else if (dgravity == 2 || dgravity == 4)
			{
				SetState(DOMES_STATE_ATTACK_LEFT_RIGHT);
				vy = 0;
			}
		}
		else if (dgravity == 1)
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
		break;

	case -1:
		if (isDamaged == true)
		{
			if (dgravity == 1 || dgravity == 3)
			{
				SetStatenoclock(DOMES_STATE_ATTACK_TOP_BOTTOM);
				vx = 0;
			}
			else if (dgravity == 2 || dgravity == 4)
			{
				SetStatenoclock(DOMES_STATE_ATTACK_LEFT_RIGHT);
				vy = 0;
			}
		}
		else if (dgravity == 1)
		{
			vy -= DOMES_GRAVITY;
			SetStatenoclock(DOMES_STATE_WALKING_TOP_BOTTOM_RIGHT);
		}
		else if (dgravity == 2)
		{
			vx += DOMES_GRAVITY;
			SetStatenoclock(DOMES_STATE_WALKING_LEFT_RIGHT_BOTTOM);
		}
		else if (dgravity == 3)
		{
			vy += DOMES_GRAVITY;
			SetStatenoclock(DOMES_STATE_WALKING_TOP_BOTTOM_LEFT);
		}
		else if (dgravity == 4)
		{
			vx -= DOMES_GRAVITY;
			SetStatenoclock(DOMES_STATE_WALKING_LEFT_RIGHT_TOP);
		}
		break;
		
	default:
		break;
	}
#pragma endregion
	
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
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		switch (dgravity)

		{
		case 3:
			
			if (nx == 1)
			{
				if (vx < 0)
				{
					this->dgravity = 4;
					vx = 0;
				}

				else
					this->dgravity = 2;
			}
			else if (nx == 0 && ny == -1)
			{
				for (int i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult.at(i);
					if (dynamic_cast<Brick*>(e->obj))
					{
						Brick* brick = dynamic_cast<Brick*>(e->obj);

						if (x > (brick->frameW + brick->x + 0.4f)) // BUG CHUA FIXXXX
						{
							this->dgravity = 4;
							nx = 0;
							vx = 0;
							vy = 0;

						}

					}
				}

			}
			else if (ny == 1)
			{
				dgravity = 1;
				directionclock = -1;
				isDamaged = false;
			}
			break;
		case 4:
			if (ny == 1 && vx < 0)
			{
				this->dgravity = 1;

			}
			else if (ny == 0)
			{
				for (int i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult.at(i);
					if (dynamic_cast<Brick*>(e->obj))
					{
						Brick* brick = dynamic_cast<Brick*>(e->obj);

						if (y > (brick->frameH + brick->y - 0.5f)) 
						{
							this->dgravity = 1;
							nx = 0;

						}

					}
				}
			}
			else if (nx == -1)
			{
				dgravity = 2;
				directionclock = 1;
				isDamaged = false;
			}

			break;

		case 1:
			if (nx == 1 && vx < 0 && vy < 0)
			{
				this->dgravity = 4;
				vx = 0;

			}
			else if (nx == -1 && vx > 0 && vy < 0)
			{
				this->dgravity = 2;
				vx = 0;
			}
			else if (nx == 0 && ny == 1)
			{
				for (int i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult.at(i);
					if (dynamic_cast<Brick*>(e->obj))
					{
						Brick* brick = dynamic_cast<Brick*>(e->obj);

						if ((x + DOMES_BBOX_WIDTH > (brick->frameW + brick->x + DOMES_BBOX_WIDTH - 0.4f)) && (vx > 0))
						{
							this->dgravity = 4;
							vy = 0;

						}
						else if (x + DOMES_BBOX_WIDTH < brick->x && vx < 0)
						{
							this->dgravity = 2;
							vy = 0;
						}
					}
				}
			}
			else if (ny == -1)
			{
				dgravity = 3;
				directionclock = -1;
				isDamaged = false;
			}
			

			break;

		case 2:
			if (vy > 0 && nx == -1 && ny == 0)
			{
				for (int i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult.at(i);
					if (dynamic_cast<Brick*>(e->obj))
					{
						Brick* brick = dynamic_cast<Brick*>(e->obj);

						if (y + 0.5f > (brick->frameH + brick->y))
						{
							this->dgravity = 1;
							nx = 0;

						}
					}
				}
			}
			else if (vy < 0 && ny == 1)
			{
				this->dgravity = 1;
				vy = 0;
			}
			else if (nx == 1)
			{
				dgravity = 4;
				directionclock = -1;
				isDamaged = false;
			}

			break;
		default:

			break;
		}


		//DebugOut(L"\ndgravity:  %d", this->dgravity);

		//DebugOut(L"\nvx:  %f", this->vx);
		//DebugOut(L"\nvy:  %f", this->vy);
		//DebugOut(L"\ndames:  %d", isDamaged);
		
		
	}
	
	
#pragma endregion
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Domes::Render()
{
	int ani;

	switch (dgravity)
	{
	case 1:

		if (isDamaged)
		{
			ani = DOMES_ANI_ATTACK_TOP_BOTTOM;
			animationSet->at(ani)->RenderTopBottom(1, x, y);
		}
		else if (vx > 0)
		{
			ani = DOMES_ANI_WALKING_TOP_BOTTOM_LEFT;
			animationSet->at(ani)->RenderTopBottom(1, x, y);
		}
		else
		{
			ani = DOMES_ANI_WALKING_TOP_BOTTOM_RIGHT;
			animationSet->at(ani)->RenderTopBottom(1, x, y);
		}
		break;

	case 2:
		if (isDamaged)
		{
			ani = DOMES_ANI_ATTACK_LEFT_RIGHT;
			animationSet->at(ani)->Render(1, x, y);
		}
		else if (vy > 0)
		{
			ani = DOMES_ANI_WALKING_LEFT_RIGHT_BOTTOM;
			animationSet->at(ani)->Render(1, x, y);
		}
		else if (vy < 0)
		{
			ani = DOMES_ANI_WALKING_LEFT_RIGHT_TOP;
			animationSet->at(ani)->Render(1, x, y);
		}
		break;

	case 3:
		if (isDamaged)
		{
			ani = DOMES_ANI_ATTACK_TOP_BOTTOM;
			animationSet->at(ani)->RenderTopBottom(-1, x, y);
		}
		else if (vx > 0)
		{
			ani = DOMES_ANI_WALKING_TOP_BOTTOM_LEFT;
			animationSet->at(ani)->RenderTopBottom(-1, x, y);
		}
		else
		{
			ani = DOMES_ANI_WALKING_TOP_BOTTOM_RIGHT;
			animationSet->at(ani)->RenderTopBottom(-1, x, y);
		}
		break;

	case 4:
		if (isDamaged)
		{
			ani = DOMES_ANI_ATTACK_LEFT_RIGHT;
			animationSet->at(ani)->Render(-1, x, y);
		}
		else if (vy > 0)
		{
			ani = DOMES_ANI_WALKING_LEFT_RIGHT_BOTTOM;
			animationSet->at(ani)->Render(-1, x, y);
		}
		else if (vy < 0)
		{
			ani = DOMES_ANI_WALKING_LEFT_RIGHT_TOP;
			animationSet->at(ani)->Render(-1, x, y);
		}
		break;

	default:
		break;
	}

			
	RenderBoundingBox();
}

Domes::Domes(float x, float y, LPGAMEENTITY t)
{
	//SetState(DOMES_STATE_WALKING_TOP_BOTTOM_RIGHT);
	enemyType = DOMES;
	this->x = x;
	this->y = y;
	this->dgravity = 3;
	nx = 1;
	this->target = t;
	health = DOMES_MAXHEALTH;
	isActive = false;
	directionclock = 1;
	isDamaged = false;
}

void Domes::StartAttack()
{
	switch (dgravity)
	{
	case 1:
		if (target->x <= x + DOMES_BBOX_WIDTH && target->x >= x && target->y > y)
		{
			isDamaged = true;

		}
		break;
	case 2:
		if (target->y <= y + DOMES_BBOX_HEIGHT && target->y >= y && target->x < x)
		{
			isDamaged = true;
		}
		break;
	case 3:
		if (target->x <= x + DOMES_BBOX_WIDTH && target->x >= x && target->y < y)
		{
			isDamaged = true;
		}
		break;
	case 4:
		if (target->y <= y + DOMES_BBOX_HEIGHT && target->y >= y && target->x > x)
		{
			isDamaged = true;
		}
		break;


	default:
		break;
	}
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
	case DOMES_STATE_ATTACK_LEFT_RIGHT:
		if (dgravity == 4)
		{
			vx += DOMES_WALKING_SPEED;
		}
		else if (dgravity == 2)
		{
			vx -= DOMES_WALKING_SPEED;
		}
		break;
	case DOMES_STATE_ATTACK_TOP_BOTTOM:
		if (dgravity == 1)
		{
			vy += DOMES_WALKING_SPEED;
		}
		else if (dgravity == 3)
		{
			vy -= DOMES_WALKING_SPEED;
		}
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

void Domes::SetStatenoclock(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case DOMES_STATE_DIE:
		y += DOMES_BBOX_HEIGHT - DOMES_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case DOMES_STATE_ATTACK_LEFT_RIGHT:
		if (dgravity == 4)
		{
			vx += DOMES_WALKING_SPEED;
		}
		else if (dgravity == 2)
		{
			vx -= DOMES_WALKING_SPEED;
		}
		break;
	case DOMES_STATE_ATTACK_TOP_BOTTOM:
		if (dgravity == 1)
		{
			vy += DOMES_WALKING_SPEED;
		}
		else if (dgravity == 3)
		{
			vy -= DOMES_WALKING_SPEED;
		}
		break;
	case DOMES_STATE_WALKING_TOP_BOTTOM_RIGHT:
		vx = -DOMES_WALKING_SPEED;
		break;
	case DOMES_STATE_WALKING_TOP_BOTTOM_LEFT:
		vx = DOMES_WALKING_SPEED;
		break;
	case DOMES_STATE_WALKING_LEFT_RIGHT_TOP:
		vy = DOMES_WALKING_SPEED;
		break;
	case DOMES_STATE_WALKING_LEFT_RIGHT_BOTTOM:
		vy = -DOMES_WALKING_SPEED;
		break;

	}
}
