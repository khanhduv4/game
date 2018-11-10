﻿#include "LargeHeart.h"


 
LargeHeart::LargeHeart(float X, float Y)
{
	_texture = new GTexture("Resources\\item\\1.png");
	_sprite = new GSprite(_texture, 100);
	type = eID::LARGEHEART;

	this->x = X;
	this->y = Y;
	vy = LARGEHEART_GRAVITY;
	TimeDisplayMax = LARGEHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;
}

void LargeHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void LargeHeart::Update(DWORD dt, vector<LPOBJECT>* listObject)
{

	TimeDisplayed += dt;
	if (TimeDisplayed >= TimeDisplayMax)
	{
		isFinish = true;
		return;
	}

	Item::Update(dt); // Update dt, dx, dy

	vector<LPOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < listObject->size(); i++)
		if (listObject->at(i)->GetType() == eID::BRICK)
			listObject_Brick.push_back(listObject->at(i));

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{ 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	  
		y += min_ty * dy + ny * 0.4f; 
 
		if (ny != 0)
		{
			vy = 0;
 		} 
	}

 	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}
 

LargeHeart::~LargeHeart()
{
}