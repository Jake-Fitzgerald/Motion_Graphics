#pragma once

// Note:
// Scrolling is handled by moving every rectangle shape down in the y axis
// 1 = collidable terrain
// 0 = non-collidable terrain
// 2 = enemy
// 3 = collectible

class Terrain
{
public:
	int terrain[15] =
	{
		1, 1, 1, 1, 1, 0, 0, 0 , 0, 0 , 0, 2, 3, 1, 1
	};

	bool b_isCollidable = false;

	const int COLS_AMOUNT = 15;
	const int ROWS_AMOUNT = 30;
	// 15 by 30 = 450


private:

};