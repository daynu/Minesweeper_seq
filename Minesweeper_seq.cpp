
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

Cell background[SIZE][SIZE];
char foreground[SIZE][SIZE];

void floodfill0(int x, int y)
{
	if (foreground[x][y] == 'H')
	{
		foreground[x][y] = char(background[x][y].number_of_mines + 48);
		if (background[x][y].number_of_mines == 0)
		{
			if (x > 0) floodfill0(x - 1, y);
			if (x > 0 && y < 9) floodfill0(x - 1, y + 1);
			if (y < 9) floodfill0(x, y + 1);
			if (x < 9 && y < 9) floodfill0(x + 1, y + 1);
			if (x < 9) floodfill0(x + 1, y);
			if (x < 9 && y > 0) floodfill0(x + 1, y - 1);
			if (y > 0) floodfill0(x, y - 1);
			if (x > 0 && y > 0) floodfill0(x - 1, y - 1);
		}
	}
}

int main()
{	
	srand(time(NULL));
	int first_tile_x = rand() % SIZE;
	int first_tile_y = rand() % SIZE;
	cout << "First tile: " << first_tile_x << " " << first_tile_y << endl;
	cout.flush();
	

	int number_of_mines = 0;

	//place mines
	while (number_of_mines < 10)
	{
		int x = rand() % SIZE;
		int y = rand() % SIZE;

		//if (x == first_tile_x && y == first_tile_y)
		if (x >= first_tile_x - 1 && x <= first_tile_x + 1 && y >= first_tile_y - 1 && y <= first_tile_y + 1)
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

	//print the board background
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (background[i][j].is_mine)
			{
				cout << "@ ";
			}
			else
			{
				cout << background[i][j].number_of_mines<< " ";
			}
		}
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			foreground[i][j] = 'H';
	
	floodfill0(first_tile_x, first_tile_y);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			cout << foreground[i][j] << " ";
		cout << endl;
	}


	cout << "Any key to exit";
	cin.get();


}

