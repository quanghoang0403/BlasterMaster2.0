#pragma once

#include <vector>
#include "Entity.h"
#include "define.h"

class Unit
{
	friend class Grid;

private:
	Grid* grid;
	LPGAMEENTITY obj;
	float x;
	float y;

	Unit* prev;
	Unit* next;

public:
	Unit(Grid* grid, LPGAMEENTITY  obj, float x, float y, int cell_x = -1, int cell_y = -1);
	void Move(float x, float y);
	LPGAMEENTITY GetObj() { return this->obj; }

};

typedef Unit* LPUNIT;

class Grid
{
	int map_width;
	int map_height;

	int cell_width;
	int cell_height;

	int numberOfColumns;
	int numberOfRows;

	vector<vector<LPUNIT>> cells;

public:
	Grid(int map_width, int map_height);
	~Grid();

	void Add(LPUNIT unit, int cell_x, int cell_y);
	void Get(D3DXVECTOR3 camPosition, vector<LPUNIT>& listUnits); // lấy tất cả các Unit* nằm trong vùng viewport -+ 1 để Update và Render
	void Move(LPUNIT unit, float x, float y); // lấy tất cả các Unit* nằm trong vùng viewport để Update và Render
	void Reset(int map_width, int map_height);
	//void Out();
};

