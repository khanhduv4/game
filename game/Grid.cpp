﻿#include "Grid.h"
 
Grid::Grid()
{
}
 
Grid::~Grid()
{
	//for (std::vector<GameObject*>::iterator it = listObjectGame.begin(); it != listObjectGame.end(); ++it)
	//{
	//	delete (*it);
	//} 
	//listObjectGame.clear();
	
}

void Grid::ReadFileToGrid(char * filename)
{
 	ifstream inp;
	inp.open(filename, ios::in);
	 
	int id, type, direction, x, y, w, h, model;

	if (inp)
	{
		int n;
		inp >> n;

		for (int i = 0; i < n; i++)
		{
			inp >> id >> type >> direction >> x >> y >> w >> h >> model;
			Insert(id, type, direction, x, y, w, h, model);
		} 
		inp.close();
	} 
}

void Grid::GetListObject(vector<GameObject*>& ListObj, Camera * camera)
{
	ListObj.clear(); // clear list

	unordered_map<int, GameObject*> mapObject;
	//mapObject.clear();


	int rowBottom = (int) floor((camera->GetYCam() + camera->GetHeight() - 1) / (float)(GRID_CELL_HEIGHT));
	int rowTop = (int)floor((camera->GetYCam() + 1) / (float)(GRID_CELL_HEIGHT));

	int colLeft = (int)floor((camera->GetXCam() + 1) / (float)(GRID_CELL_WIDTH));
	int colRight = (int)floor((camera->GetXCam() + camera->GetWidth() -1) / (float)(GRID_CELL_WIDTH));


	for (int row = rowTop; row <= rowBottom; row++)
		for (int col = colLeft; col <= colRight; col++)
		{
			for (UINT i = 0; i < cells[row + GRID_BASE][col + GRID_BASE].size(); i++)
			{
				if (cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetHealth() > 0) // còn tồn tại
				{ 
						if (mapObject.find(cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetId()) == mapObject.end()) // ko tìm thấy
							mapObject[cells[row + GRID_BASE][col + GRID_BASE].at(i)->GetId()] = cells[row + GRID_BASE][col + GRID_BASE].at(i);
				}
				else
				{
				//	cells[row + GRID_BASE][col + GRID_BASE].erase(cells[row + GRID_BASE][col + GRID_BASE].begin() + i); // xóa luôn
				}
			}
		}

	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}

}

void Grid::Insert(int id, int type, int direction, int x, int y, int w, int h, int Model)
{ 
	int Top = (int)floor(y / (float)(GRID_CELL_HEIGHT));
	int Bottom = (int)floor((y + h) / (float)(GRID_CELL_HEIGHT));

	int Left = (int)floor(x / (float)(GRID_CELL_WIDTH));
	int Right = (int)floor((x + w) / (float)(GRID_CELL_WIDTH));

	GameObject * dataObject = GetNewObject(type, x, y, w, h, Model);
	if (dataObject == NULL)
	{
		DebugOut(L"[Insert Object GRID Fail] :  Khong tao duoc object!\n");
		return;
	}
	dataObject->SetId(id);
	dataObject->SetDirection(direction);
 
 
	for (int row = Top; row <= Bottom; row++)
	{
		for (int col = Left; col <= Right; col++)
		{
			cells[row + GRID_BASE][col + GRID_BASE].push_back(dataObject);
		}
	}

}


GameObject * Grid::GetNewObject(int type, int x, int y,int w, int h, int Model)
{
	if (type == eType::BRICK) return new Brick(x, y, w, h, Model);
	if (type == eType::TORCH) return new Torch(x, y);
	if (type == eType::OBJECT_HIDDEN) return new ObjectHidden(x, y, w, h);
	if (type == eType::CANDLE) return new Candle(x, y);

	if (type == eType::STAIR_TOP) return new StairTop(x, y);
	if (type == eType::STAIR_BOTTOM) return new StairBottom(x, y);
	if (type == eType::GATE) return new Gate(x, y);

	return NULL;
}
 