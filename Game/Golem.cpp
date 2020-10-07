#include "Golem.h"
#include "Player.h"
void Golem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOLEM_BBOX_WIDTH;
	bottom = y + GOLEM_BBOX_HEIGHT;
}


void Golem::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	// Calculate dx, dy 
	vx = nx * GOLEM_WALKING_SPEED;
	Entity::Update(dt);
#pragma region Xử lý vy
	// Simple fall down
	vy += GOLEM_GRAVITY * dt;

	
	
#pragma endregion





#pragma region Xử lý va chạm
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> bricks;

	coEvents.clear();
	bricks.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == EntityType::BRICK)
			bricks.push_back(coObjects->at(i));




	// turn off collision when die 
	if (state != GOLEM_STATE_DIE)
		CalcPotentialCollisions(&bricks, coEvents);


	//DebugOut(L"%4.2f, %4.2f\n", dx, dy);

	// No collision occured, proceed normally
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


		if (nx != 0)
		{
			Golem::nx = -Golem::nx;
		}
		if (ny != 0)
		{
			vy = 0;
			for (int i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult.at(i);
				if (e->ny != 0)
				{
					RECT rect = static_cast<Brick*>(e->obj)->GetBBox();
					if (x + GOLEM_BBOX_WIDTH > rect.right)
					{
						Golem::nx = -Golem::nx;
						x += rect.right - (x + GOLEM_BBOX_WIDTH) - nx * 0.4f;
					}
					else if (x < rect.left)
					{
						Golem::nx = -Golem::nx;
						x += rect.left - x + nx * 0.4f;
					}
					break;
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion
}

void Golem::Render()
{
	if (vx > 0)
		direction = 1;
	else
		direction = -1;

	int ani = GOLEM_ANI_WALKING;
	if (state == GOLEM_STATE_DIE) {
		ani = GOLEM_ANI_DIE;
	}
	//DebugOut(L"[xxxxxx] direction: %s\n", direction);
	animationSet->at(ani)->Render(direction, x, y);

	RenderBoundingBox();
}


Golem::Golem()
{
	SetState(GOLEM_STATE_WALKING);
	nx = 1;
}

void Golem::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case GOLEM_STATE_DIE:
		y += GOLEM_BBOX_HEIGHT - GOLEM_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GOLEM_STATE_WALKING:
		vx = -GOLEM_WALKING_SPEED;
	}
}
