#include "Entity.h"

Entity::Entity()
{
	posX = posY = 0;
	vX = vY = 0;
	direction = 1;

	health = 1;
	isDead = false;
	unsighted = false;
	isStaticObj = false;

	bbARGB = 0;
}

Entity::~Entity() {}

void Entity::Update(DWORD dt, vector<LPGAMEENTITY>* coObjects)
{
	this->dt = dt;
	dx = vX * dt;
	dy = vY * dt;
}

void Entity::RenderBoundingBox()
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(0);
	Game::GetInstance()->Draw(direction, l, t, bbox, rect.left, rect.top, rect.right, rect.bottom, bbARGB);
}

/*
	Extension of original SweptAABB to deal with two moving listObjects
*/
LPCOLLISIONEVENT Entity::SweptAABBEx(LPGAMEENTITY coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->ReceiveSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	//		STARRRR
	//Do BBox theo logic SweptAABB la xet cac rect voi origin la goc trai tren
	//Nhu vay logic se ap dung cho Draw voi origin la goc trai tren
	//Su dung origin la tam textTexture -> xet cac rect lech theo huong tam textTexture
	LPSPRITE sprt = animationSet->at(0)->GetAnimationCurrentFrame(0)->GetSprite();
	LPSPRITE coSprt = coO->animationSet->at(0)->GetAnimationCurrentFrame(0)->GetSprite();
	Game::SweptAABB(
		ml - (float)sprt->GetFrameWidth() / 2,
		mt - (float)sprt->GetFrameHeight() / 2,
		mr - (float)sprt->GetFrameWidth() / 2,
		mb - (float)sprt->GetFrameHeight() / 2,
		dx, dy,
		sl - (float)coSprt->GetFrameWidth() / 2,
		st - (float)coSprt->GetFrameHeight() / 2,
		sr - (float)coSprt->GetFrameWidth(),
		sb - (float)coSprt->GetFrameHeight() / 2,
		t, nx, ny
	);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable listObjects

	coObjects: the list of colliable listObjects
	coEvents: list of potential collisions
*/
void Entity::CalcPotentialCollisions(
	vector<LPGAMEENTITY>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void Entity::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

bool Entity::IsCollidingObject(Entity* Obj)
{
	float ml, mt, mr, mb;		// moving object bbox
	this->GetBoundingBox(ml, mt, mr, mb);

	float sl, st, sr, sb;		// static object bbox
	Obj->GetBoundingBox(sl, st, sr, sb);

	//Check AABB first
	LPSPRITE sprt = animationSet->at(0)->GetAnimationCurrentFrame(0)->GetSprite();
	LPSPRITE coSprt = Obj->animationSet->at(0)->GetAnimationCurrentFrame(0)->GetSprite();
	if (Game::GetInstance()->IsCollidingAABB(
		ml - (float)sprt->GetFrameWidth() / 2,
		mt - (float)sprt->GetFrameHeight() / 2,
		mr - (float)sprt->GetFrameWidth() / 2,
		mb - (float)sprt->GetFrameHeight() / 2,
		sl - (float)coSprt->GetFrameWidth() / 2,
		st - (float)coSprt->GetFrameHeight() / 2,
		sr - (float)coSprt->GetFrameWidth(),
		sb - (float)coSprt->GetFrameHeight() / 2))
		return true;

	//Swept AABB later
	LPCOLLISIONEVENT e = SweptAABBEx(Obj);
	bool isColliding = e->t > 0 && e->t <= 1;
	return isColliding;
}


float Entity::GetDistance(D3DXVECTOR2 pos, D3DXVECTOR2 target)
{
	return (float)sqrt(pow(pos.x - target.x, 2) + pow(pos.y - target.y, 2));
}

D3DXVECTOR2 Entity::RadialMovement(D3DXVECTOR2 focus, D3DXVECTOR2 pos, float speed)
{
	float dist = GetDistance(pos, focus);
	if (dist < speed)
		return focus - pos;
	else
		return (focus - pos) * speed / dist;
}
