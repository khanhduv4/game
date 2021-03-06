﻿#include "Ghost.h"

 

Ghost::Ghost(float X,  float Y, int Direction)
{
	x = X;
	y = Y;
	this->direction = Direction;

	texture = TextureManager::GetInstance()->GetTexture(eType::GHOST);
	sprite = new GSprite(texture, 100);

	Health = 1; // sét máu
	type = eType::GHOST;
	vx = GHOST_SPEED_X* this->direction;
}

Ghost::~Ghost()
{
}
 
void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt); 
	vy += GHOST_GRAVITY * dt;

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == eType::BRICK)
			listObject_Brick.push_back(coObjects->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm 
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0)
		{ 
			vx *= -1;
			direction *= -1;
		}

		if (ny != 0)
		{
			vy = 0;
			//vx = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];


	sprite->Update(dt); // update frame ani
}

void Ghost::Render(Camera * camera)
{
	if (Health <= 0)
		return;
	 
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		sprite->Draw(pos.x, pos.y);
	else
		sprite->DrawFlipX(pos.x, pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

}
