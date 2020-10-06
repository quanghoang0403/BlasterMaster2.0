﻿#include <algorithm>
#include <assert.h>
#include "debug.h"

#include "Player.h"
#include "Game.h"

#include "Gate.h"

Player::Player(float x, float y) : Entity()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_PLAYER));//can 1 dong nhu nay`ok!!
	untouchable = 0;
	SetState(SOPHIA_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	backup_JumpY = 0;
	health = 7;
}

void Player::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	// Calculate dx, dy 
	Entity::Update(dt);
#pragma region Xử lý vy
	// Simple fall down
	vy += SOPHIA_GRAVITY * dt;
	//Check hightPlayer
	if (isJumping && backup_JumpY - y >= HIGHT_LEVER1 && isJumpHandle == false) {
		if (!isPressJump)
			vy = 0;
		isJumpHandle = true;
	}
#pragma endregion

#pragma region Xử lý vx
	//if (direction > 0)
	//{
	//	if (vx - SOPHIA_WALKING_SPEED_BONUS > 0)
	//		vx -= SOPHIA_WALKING_SPEED_BONUS;
	//	else
	//		vx = 0;
	//}
	//else
	//{
	//	if (vx + SOPHIA_WALKING_SPEED_BONUS < 0)
	//		vx += SOPHIA_WALKING_SPEED_BONUS;
	//	else
	//		vx = 0;
	//}
#pragma endregion

#pragma region Xử lý gun flip
	if (isPressFlipGun == false)
	{
		animationSet->at(SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_1)->ResetCurrentFrame();
		animationSet->at(SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_2)->ResetCurrentFrame();
		animationSet->at(SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_3)->ResetCurrentFrame();
		animationSet->at(SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_4)->ResetCurrentFrame();
		animationSet->at(SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_1)->ResetCurrentFrame();
		animationSet->at(SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_2)->ResetCurrentFrame();
		animationSet->at(SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_3)->ResetCurrentFrame();
		animationSet->at(SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_4)->ResetCurrentFrame();
		animationSet->at(SOPHIA_ANI_GUN_FLIP_RIGHT)->ResetCurrentFrame();
		animationSet->at(SOPHIA_ANI_GUN_FLIP_LEFT)->ResetCurrentFrame();
	}
#pragma endregion

#pragma region Xử lý va chạm
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SOPHIA_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

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

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		//block every object first!
		//x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;

		//if (nx != 0) vx = 0;
		//if (ny != 0) vy = 0;
		//if (ny < 0)
		//{
		//	isJumping = false;
		//}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetType() == EntityType::BRICK)
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
				if (e->ny != 0)
				{

					if (e->ny == -1)
					{
						vy = 0;
						isJumping = false;
					}
				
					if (e->nx != 0)
					{
						vx = 0;
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion

}

void Player::Render()
{
	RenderBoundingBox();
	//LPANIMATION lpp;
	//int a = lpp->GetFrame();
	//DebugOut(L"[INFO] Start loading game file : %s\n",a);

#pragma region Khai báo biến
	int ani = -1;
	int alpha = 255;
	int current_frame; //luu frame khi dang di chuyen ma dung lai
	if (untouchable) alpha = 128;
#pragma endregion

	if (state == SOPHIA_STATE_DIE)
	{
		ani = SOPHIA_JASON_ANI_DIE;
		/*animation_set->at(ani)->RenderFrame(8,x, y, alpha);*/
	}

	else if (isPressFlipGun == true)
	{
		if (vx == 0)
		{
			if (direction > 0)
			{
				//idle theo walking
				current_frame = animationSet->at(SOPHIA_ANI_JASON_WALKING_RIGHT)->GetFrameStopWalking();
				switch (current_frame)
				{
				case SOPHIA_STOP_WALKING_SPRITE2:
					ani = SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_2;
					break;
				case SOPHIA_STOP_WALKING_SPRITE3:
					ani = SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_3;
					break;
				case SOPHIA_STOP_WALKING_SPRITE4:
					ani = SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_4;
					break;
				default:
					ani = SOPHIA_ANI_GUN_FLIP_IDLE_RIGHT_1;
					break;
				}
			}
			else
			{
				current_frame = animationSet->at(SOPHIA_ANI_JASON_WALKING_LEFT)->GetFrameStopWalking();
				switch (current_frame)
				{
				case SOPHIA_STOP_WALKING_SPRITE2:
					ani = SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_2;
					break;
				case SOPHIA_STOP_WALKING_SPRITE3:
					ani = SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_3;
					break;
				case SOPHIA_STOP_WALKING_SPRITE4:
					ani = SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_4;
					break;
				default:
					ani = SOPHIA_ANI_GUN_FLIP_IDLE_LEFT_1;
					break;
				}
			}

			if (isGunFlipping == false)
			{
				animationSet->at(ani)->OldRender(x, y - SOPHIA_JASON_HEIGHT_GUN_FLIP, alpha);
				if (animationSet->at(ani)->GetFrame() == 1)
				{
					//DebugOut(L"[frame]: %d;\n", animation_set->at(SOPHIA_ANI_JASON_WALKING_RIGHT)->GetFrame());
					isGunFlipping = true;
				}
				return;

			}
			else
			{
				animationSet->at(ani)->RenderFrame(1, x, y - SOPHIA_JASON_HEIGHT_GUN_FLIP, alpha);
				return;
			}
		}
		else if (vx > 0)
			ani = SOPHIA_ANI_GUN_FLIP_RIGHT;
		else
			ani = SOPHIA_ANI_GUN_FLIP_LEFT;

		if (isGunFlipping == false)
		{
			animationSet->at(ani)->RenderGunFlip(x, y - SOPHIA_JASON_HEIGHT_GUN_FLIP, alpha);
			if (animationSet->at(ani)->GetFrame() > 3)
			{
				//DebugOut(L"[frame]: %d;\n", animation_set->at(SOPHIA_ANI_JASON_WALKING_RIGHT)->GetFrame());
				isGunFlipping = true;
			}
			return;
		}
		else
		{
			animationSet->at(ani)->RenderGunFlipTargetTop(x, y - SOPHIA_JASON_HEIGHT_GUN_FLIP, alpha);
			return;
		}
	}

	else
	{
		if (isJumping == false)
		{
			if (vx == 0)
			{
				if (direction > 0)
				{
					ani = SOPHIA_ANI_JASON_WALKING_RIGHT;
					current_frame = animationSet->at(ani)->GetFrameStopWalking();
					//DebugOut(L"[frame]: %d;\n", animation_set->at(SOPHIA_ANI_JASON_WALKING_RIGHT)->GetFrameStopWalking());
				}
				else
				{
					ani = SOPHIA_ANI_JASON_WALKING_LEFT;
					current_frame = animationSet->at(ani)->GetFrameStopWalking();
				}
				animationSet->at(ani)->RenderFrame(current_frame, x, y, alpha);// ve frame idle
				isGunFlipping = false;
				return;
			}
			else if (vx > 0)
				ani = SOPHIA_ANI_JASON_WALKING_RIGHT;
			else ani = SOPHIA_ANI_JASON_WALKING_LEFT;
			animationSet->at(ani)->OldRender(x, y, alpha);
			isGunFlipping = false;
		}
		else
		{
			if (vx == 0 && vy > 0)
			{
				if (direction > 0) ani = SOPHIA_ANI_JASON_JUMP_DOWN_IDLE_RIGHT;
				else ani = SOPHIA_ANI_JASON_JUMP_DOWN_IDLE_LEFT;
			}
			else if (vx == 0 && vy <= 0)
			{
				if (direction > 0) ani = SOPHIA_ANI_JASON_JUMP_UP_IDLE_RIGHT;
				else ani = SOPHIA_ANI_JASON_JUMP_UP_IDLE_LEFT;
			}
			else if (vy > 0)
			{
				if (vx > 0) ani = SOPHIA_ANI_JASON_JUMP_DOWN_WALKING_RIGHT;
				else ani = SOPHIA_ANI_JASON_JUMP_DOWN_WALKING_LEFT;
			}
			else if (vy <= 0)
			{
				if (vx > 0) ani = SOPHIA_ANI_JASON_JUMP_UP_WALKING_RIGHT;
				else ani = SOPHIA_ANI_JASON_JUMP_UP_WALKING_LEFT;
			}
			isGunFlipping = false;
			animationSet->at(ani)->OldRender(x, y, alpha);
			return;
		}
	}

}

void Player::SetState(int state)
{
	Entity::SetState(state);

	switch (state)
	{
		/*case SOPHIA_STATE_WALKING_RIGHT:
			if (vx < SOPHIA_WALKING_SPEED)
			{
				vx = vx * 2 + SOPHIA_WALKING_SPEED_UNIT;
				direction = 1;
			}

			break;
		case SOPHIA_STATE_WALKING_LEFT:
			if (vx > -SOPHIA_WALKING_SPEED)
			{
				vx = vx * 2 - SOPHIA_WALKING_SPEED_UNIT;
				direction = -1;
			}
			break;*/
	case SOPHIA_STATE_WALKING_RIGHT:
		vx = SOPHIA_WALKING_SPEED;
		direction = 1;
		break;
	case SOPHIA_STATE_WALKING_LEFT:
		vx = -SOPHIA_WALKING_SPEED;
		direction = -1;
		break;
	case SOPHIA_STATE_JUMP:
		isPressJump = true;
		if (isJumping == true)
			return;
		else
		{
			isJumpHandle = false;
			isJumping = true;
			vy = -SOPHIA_JUMP_SPEED_Y;
			backup_JumpY = y;
		}
		break;
	case SOPHIA_STATE_IDLE:
		isPressJump = false;
		vx = 0;
		break;
	case SOPHIA_STATE_DIE:
		vy = -SOPHIA_DIE_DEFLECT_SPEED;
		break;
		/*case SOPHIA_STATE_GUN_UNFLIP:
			isGunFlipping = false;
			break;*/
	}
}


void Player::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SOPHIA_JASON_BBOX_WIDTH;
	bottom = y + SOPHIA_JASON_BBOX_HEIGHT;
}

void Player::Reset()
{
	SetState(SOPHIA_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}
