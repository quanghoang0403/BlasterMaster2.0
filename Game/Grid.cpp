#include "Grid.h"


Unit::Unit(Grid* grid, LPGAMEENTITY obj, float x, float y, int cell_x, int cell_y)
{
	this->grid = grid;
	this->obj = obj;

	this->x = x;
	this->y = y;

	this->prev = NULL;
	this->next = NULL;

	grid->Add(this, cell_x, cell_y);
}

void Unit::Move(float x, float y)
{
	grid->Move(this, x, y);
}

Grid::Grid(int map_width, int map_height)
{
	this->map_width = map_width;
	this->map_height = map_height;

	this->numberOfRows = (int)(map_width/ (SCREEN_WIDTH/2));
	this->numberOfColumns = (int)(map_height / (SCREEN_HEIGHT/ 2));

	this->cell_width = SCREEN_WIDTH / 2;
	this->cell_height = SCREEN_HEIGHT / 2;

	cells.resize(numberOfRows);

	for (int i = 0; i < numberOfRows; i++)
		cells[i].resize(numberOfColumns);

	for (int i = 0; i < numberOfRows; i++)
		for (int j = 0; j < numberOfColumns; j++)
			cells[i][j] = NULL;
}

Grid::~Grid()
{
}

void Grid::Add(LPUNIT unit, int cell_x, int cell_y)
{
	if (cell_x == -1) { // trường hợp add unit không từ file vd: item rớt ra từ candle
		cell_x = (int)(unit->y / cell_height);
		cell_y = (int)(unit->x / cell_width);
	}


	// thêm vào đầu cell - add head
	unit->prev = NULL;
	unit->next = cells[cell_x][cell_y];
	cells[cell_x][cell_y] = unit;

	if (unit->next != NULL)
		unit->next->prev = unit;
}

void Grid::Get(D3DXVECTOR3 camPosition, vector<LPUNIT>& listUnits)
{
	//int start_col = (int)(camPosition.x / cell_width);
	//int end_col = ceil((camPosition.x + SCREEN_WIDTH) / cell_width);

	//if (start_col - 1 >= 0) start_col -= 1; // xét thêm 1 grid trước viewport
	//if (end_col == numberOfColumns) end_col -= 1;

	//for (int i = 0; i < numberOfRows; i++)
	//{
	//	for (int j = start_col; j <= end_col; j++) // xét thêm 1 grid sau viewport (j<= ...)
	//	{

	//		Unit* unit = cells[i][j];

	//		while (unit != NULL)
	//		{
	//			if (unit->GetObj()->IsEnable() == true)
	//				listUnits.push_back(unit);
	//			unit = unit->next;
	//		}
	//	}
	//}
}

void Grid::Move(LPUNIT unit, float x, float y)
{
	// lấy chỉ số cell cũ
	int old_row = (int)(unit->y / cell_height);
	int old_col = (int)(unit->x / cell_width);

	// lấy chỉ số cell mới
	int new_row = (int)(y / cell_height);
	int new_col = (int)(x / cell_width);

	//// nếu object ra khỏi vùng viewport -> không cần cập nhật
	//if (new_row < 0 || new_row >= nums_row || new_col < 0 || new_col >= nums_col)
	//	return;

	// cập nhật toạ độ mới
	unit->x = x;
	unit->y = y;

	// cell không thay đổi
	if (old_row == new_row && old_col == new_col)
		return;

	// huỷ liên kết với cell cũ
	if (unit->prev != NULL)
	{
		unit->prev->next = unit->next;
	}

	if (unit->next != NULL)
	{
		unit->next->prev = unit->prev;
	}

	if (cells[old_row][old_col] == unit)
	{
		cells[old_row][old_col] = unit->next;
	}

	// thêm vào cell mới
	Add(unit, -1, -1);
}

void Grid::Reset(int map_width, int map_height)
{
	this->map_width = map_width;
	this->map_height = map_height;

	this->numberOfRows = (int)(map_width / (SCREEN_WIDTH / 2));
	this->numberOfColumns = (int)(map_height / (SCREEN_HEIGHT / 2));

	this->cell_width = SCREEN_WIDTH / 2;
	this->cell_height = SCREEN_HEIGHT / 2;

	cells.resize(numberOfRows);

	for (int i = 0; i < numberOfRows; i++)
		cells[i].resize(numberOfColumns);

	for (int i = 0; i < numberOfRows; i++)
		for (int j = 0; j < numberOfColumns; j++)
			cells[i][j] = NULL;
}