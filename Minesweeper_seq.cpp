
#include <iostream>
#include <algorithm>
#include <ctime>

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
float prob[SIZE][SIZE];



int floodfill0(int x, int y)
{
	if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) return 0;

	if (foreground[x][y] == 'H')
	{
		foreground[x][y] = char(background[x][y].number_of_mines + 48);
		prob[x][y] = 0.0f;
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

	return 1;
}

void printfg()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << foreground[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void printprob()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%.2f", prob[i][j]);
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void updateprob()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			int hidden_around = 0;
			if (foreground[i][j] == 'H' || int(foreground[i][j]) - 48 == 0)
			{
				continue;
			}
			if (foreground[i + 1][j] == 'H') hidden_around++;
			if (foreground[i - 1][j] == 'H') hidden_around++;
			if (foreground[i][j + 1] == 'H') hidden_around++;
			if (foreground[i][j - 1] == 'H') hidden_around++;
			if (foreground[i + 1][j + 1] == 'H') hidden_around++;
			if (foreground[i - 1][j + 1] == 'H') hidden_around++;
			if (foreground[i + 1][j - 1] == 'H') hidden_around++;
			if (foreground[i - 1][j - 1] == 'H') hidden_around++;

			if (hidden_around == int(foreground[i][j]) - 48)
			{
				if (foreground[i + 1][j] == 'H') prob[i + 1][j] = 1.0f;
				if (foreground[i - 1][j] == 'H') prob[i - 1][j] = 1.0f;
				if (foreground[i][j + 1] == 'H') prob[i][j + 1] = 1.0f;
				if (foreground[i][j - 1] == 'H') prob[i][j - 1] = 1.0f;
				if (foreground[i + 1][j + 1] == 'H') prob[i + 1][j + 1] = 1.0f;
				if (foreground[i - 1][j + 1] == 'H') prob[i - 1][j + 1] = 1.0f;
				if (foreground[i + 1][j - 1] == 'H') prob[i + 1][j - 1] = 1.0f;
				if (foreground[i - 1][j - 1] == 'H') prob[i - 1][j - 1] = 1.0f;
			}
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
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			prob[i][j] = 0.1f;

	

	int number_of_mines = 0;

	//place mines
	while (number_of_mines < 10)
	{
		int x = rand() % SIZE;
		int y = rand() % SIZE;

		if (x >= first_tile_x - 1 && x <= first_tile_x + 1 && y >= first_tile_y - 1 && y <= first_tile_y + 1)
		{
			continue;
		}

		if (!background[x][y].is_mine)
		{
			background[x][y].is_mine = true;
			background[x][y].number_of_mines = 9;
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
	//first move
	floodfill0(first_tile_x, first_tile_y);


	//second move

	updateprob();
	printprob();
	printfg();

//flood fill definite moves
	int changed;
	int count = 0;
	do
	{
		count++;
		changed = 0;
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				int flagged = 0;
				if (foreground[i][j] == 'H')
				{
					continue;
				}
				if (prob[i + 1][j] == 1.0) flagged++;
				if (prob[i - 1][j] == 1.0) flagged++;
				if (prob[i][j + 1] == 1.0) flagged++;
				if (prob[i][j - 1] == 1.0) flagged++;
				if (prob[i + 1][j + 1] == 1.0) flagged++;
				if (prob[i - 1][j + 1] == 1.0) flagged++;
				if (prob[i + 1][j - 1] == 1.0) flagged++;
				if (prob[i - 1][j - 1] == 1.0) flagged++;

				if (flagged == int(foreground[i][j]) - 48)
				{
					if (foreground[i + 1][j] == 'H' && prob[i + 1][j] != 1.0) if( floodfill0(i + 1, j) == 1) changed = 1;
					if (foreground[i - 1][j] == 'H' && prob[i - 1][j] != 1.0) if( floodfill0(i - 1, j) == 1) changed = 1;
					if (foreground[i][j + 1] == 'H' && prob[i][j + 1] != 1.0) if( floodfill0(i, j + 1) == 1) changed = 1;
					if (foreground[i][j - 1] == 'H' && prob[i][j - 1] != 1.0) if( floodfill0(i, j - 1) == 1) changed = 1;
					if (foreground[i + 1][j + 1] == 'H' && prob[i + 1][j + 1] != 1.0) if( floodfill0(i + 1, j + 1) == 1) changed = 1;
					if (foreground[i - 1][j + 1] == 'H' && prob[i - 1][j + 1] != 1.0) if( floodfill0(i - 1, j + 1) == 1) changed = 1;
					if (foreground[i + 1][j - 1] == 'H' && prob[i + 1][j - 1] != 1.0) if( floodfill0(i + 1, j - 1) == 1) changed = 1;
					if (foreground[i - 1][j - 1] == 'H' && prob[i - 1][j - 1] != 1.0) if( floodfill0(i - 1, j - 1) == 1) changed = 1;

				}
			}
		}
		updateprob();
		printprob();
		printfg();
	} while (changed == 1);

	int found = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (background[i][j].is_mine == 1 && prob[i][j] == 1) found++;
		}
	}
	if (found == number_of_mines) cout << "Found all."<<endl;
	else cout << "Didn't find all."<<endl;


	//cout << "Count = " << count << endl;
	cout << "Any key to exit";
	cin.get();


}

