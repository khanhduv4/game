#include "Item.h"



Item::Item()
{ 
	TimeDisplayed = 0;

}


Item::~Item()
{
	 
}

void Item::Update(DWORD dt, vector<LPOBJECT> *listObject)
{ 
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

void Item::Render(Camera * camera)
{
	if (isFinish == true)
		return;

	D3DXVECTOR2 pos = camera->Transform(x, y);

	_sprite->Draw((int)pos.x, (int)pos.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}
 



bool Item::GetFinish()
{
	return isFinish;
}

void Item::SetFinish(bool b)
{
	isFinish = b;
}