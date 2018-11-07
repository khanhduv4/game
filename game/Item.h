﻿#ifndef __ITEM_H__
#define __ITEM_H__

#include "GSprite.h"
#include "Camera.h"
#include "GTexture.h"
#include "GameObject.h"
#include "DebugRenderBBOX.h"
#include "define.h"
//#include "VariableGlobal.h"

class Item : public Object
{
protected: 

	int TimeDisplayMax; // thời gian tối đa cho phép hiển thị.
	int TimeDisplayed; // Thời gian đã hiển thị.

	bool isFinish; // đã kết thúc chưa?

public:
	Item();
	~Item();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPOBJECT> *listObject = NULL);
	virtual void Render(Camera * camera);
	  
 	bool GetFinish();
};




















#endif // !__ITEM_H__




