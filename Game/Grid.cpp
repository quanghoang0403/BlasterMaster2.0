#include "Grid.h"
//Unit::Unit(Grid* grid, LPGAMEENTITY obj, float x, float y)
//{
//	this->grid = grid;
//	this->obj = obj;
//
//	this->x = x;
//	this->y = y;
//
//	//this->prev = NULL;
//	//this->next = NULL;
//	grid->Add(this, x, y);
//}

Grid::Grid(int map_width, int map_height)
{
	this->map_width = map_width;
	this->map_height = map_height;

	this->numberOfColumns = (int)(map_width/ (SCREEN_WIDTH/2))+1;
	this->numberOfRows = (int)(map_height / (SCREEN_HEIGHT/ 2))+1;

	this->cell_width = SCREEN_WIDTH / 2;
	this->cell_height = SCREEN_HEIGHT / 2;

	cells.resize(numberOfRows);

	for (int i = 0; i < numberOfRows; i++)
		cells[i].resize(numberOfColumns);

	for (int i = 0; i < numberOfRows; i++)
	{
		for (int j = 0; j < numberOfColumns; j++)
		{
			cells[i][j].resize(50);
		}
	}

	for (int i = 0; i < numberOfRows; i++)
		for (int j = 0; j < numberOfColumns; j++)
			cells[i][j].clear();
}

Grid::~Grid()
{
}

//void Grid::Add(LPUNIT unit, int posX, int posY)
//{
//	//unit->x = posX;
//	//unit->y = posY;
//	int cell_x = (int)(posY / cell_height);
//	int cell_y = (int)(posX / cell_width);
//	// thêm vào đầu cell - add head
//	//unit->prev = NULL;
//	//unit->next = cells[cell_x][cell_y];
//	cells[cell_x][cell_y].push_back(unit);
//}


////vector<LPUNIT> Grid::GetList(float camX, float camY)
////{
////	vector<LPUNIT> list;
////	int start_col = (int)(camX / cell_width);
////	int start_row = (int)(camY / cell_height);
////
////	for (int j = start_col; j <= start_col + 2; j++)
////	{
////		for (int j = start_row; j <= start_row + 2; j++)
////		{
////			for (int k = 0; k <= cells[start_col][start_row].size(); k++)
////				list.push_back(cells[start_col][start_row][k]);
////		}
////	}
////	return list;
////}

void Grid::PushObjectIntoGrid(vector<LPGAMEENTITY> listObj)
{
	for (int i = 0; i < listObj.size(); i++)
	{
		int col = (int)(listObj[i]->x/ cell_width);
		int row = (int)(listObj[i]->y / cell_height);
		cells[row][col].push_back(listObj[i]);
	}
}

void Grid::GetListObject(float camX, float camY, vector<LPGAMEENTITY>& listObj)
{
	int start_col = (int)(camX / cell_width);
	int start_row = (int)(camY / cell_height);
	int end_col = start_col + 2;
	int end_row = start_row + 2;
	if (numberOfRows < end_row)
		end_row = numberOfRows;
	if (numberOfColumns < end_col)
		end_col = numberOfColumns;
	for (int j = start_col; j < end_col; j++)
	{
		for (int k = start_row; k < end_row; k++)
		{
			for (int i = 0; i < cells[start_row][start_col].size(); i++)
				listObj.push_back(cells[start_row][start_col][i]);
		}
	}
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
			cells[i][j].clear();
}