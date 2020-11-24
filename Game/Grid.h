#pragma once

#include <vector>
#include "Entity.h"
#include "define.h"

//class Unit
//{
//	friend class Grid;
//
//private:
//	Grid* grid;
//	LPGAMEENTITY obj;
//	float x;
//	float y;
//
//	//Unit* prev;
//	//Unit* next;
//
//public:
//	Unit(Grid* grid, LPGAMEENTITY  obj, float x, float y);
//	LPGAMEENTITY GetObj() { return this->obj; }
//
//};
//
//typedef Unit* LPUNIT;

class Grid
{
	int map_width;
	int map_height;

	int cell_width;
	int cell_height;

	int numberOfColumns;
	int numberOfRows;

	//vector<vector<vector<LPUNIT>>> cells;
	vector<vector<vector<LPGAMEENTITY>>> cells;
public:
	Grid(int map_width, int map_height);
	~Grid();
	void PushObjectIntoGrid(vector<LPGAMEENTITY> listObj);
	void GetListObject(float camX, float camY, vector<LPGAMEENTITY>& listObj);
	//void Add(LPUNIT unit, int cell_x, int cell_y);
	//void Get(float camX, float camY, vector<LPUNIT>& listUnits); // lấy tất cả các Unit* nằm trong vùng viewport -+ 1 để Update và Render
	void Reset(int map_width, int map_height);
	//vector<LPUNIT> GetList(float camX, float camY);
	//void Out();
};

