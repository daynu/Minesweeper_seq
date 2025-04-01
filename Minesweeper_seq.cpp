
#include <iostream>

using namespace std;

const int SIZE = 10;

class Cell
{
public:
	bool is_mine;
	int number_of_mines;

	Cell()
	{
		is_mine = false;
		number_of_mines = 0;
	}
};


int main()
{	
	srand(time(NULL));
	int first_tile_x = rand() % SIZE;
	int first_tile_y = rand() % SIZE;
	cout << "First tile: " << first_tile_x << " " << first_tile_y << endl;
	cout.flush();
	
	Cell background[SIZE][SIZE];
	
	int number_of_mines = 0;

	//place mines
	while (number_of_mines < 10)
	{
		int x = rand() % SIZE;
		int y = rand() % SIZE;

		if (x == first_tile_x && y == first_tile_y)
		{
			continue;
		}

		if (!background[x][y].is_mine)
		{
			background[x][y].is_mine = true;
			number_of_mines++;
		}
	   
	}

	//number of mines around each cell
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (background[i][j].is_mine)
			{
				continue;
			}
			else
			{
				for (int k = -1; k <= 1; k++)
				{
					for (int l = -1; l <= 1; l++)
					{
						if (k == 0 && l == 0)
						{
							continue;
						}

						if (i + k >= 0 && i + k < SIZE && j + l >= 0 && j + l < SIZE)
						{
							if (background[i + k][j + l].is_mine)
							{
								background[i][j].number_of_mines++;
							}
						}
					}
				}

			}
		}
	}

	//print the board
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (background[i][j].is_mine)
			{
				cout << "M ";
			}
			else
			{
				cout << background[i][j].number_of_mines<< " ";
			}
		}
		cout << endl;
	}

	cout << "Any key to exit";
	cin.get();


}

