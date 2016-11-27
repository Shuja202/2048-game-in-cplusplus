#pragma once

class Grid
{
	int ** data;			// a two-dimensional array
	int rc;					// number of rows and columns will always be the same
	int score, highscore;
public:
	Grid(int);				// makes grid according to user choice
	void ShowGrid();
	void SetAll(int);		// set every index to the passed integer
	void Left();
	void Right();
	void Down();
	void Up();
	void Randomize();
	int AvailableSpace();
	bool Availability();
	void Save();
	friend ofstream& operator<<(ofstream&, Grid&);
	~Grid();			// deletes the two dimensional array from heap memory
};
Grid::Grid(int x)
{
	ifstream fin;
	score = 0;
	switch (x)
	{
	case 1: rc = 3;
		fin.open("highscore3.txt");
		break;	// 3x3
	case 2: rc = 4;
		fin.open("highscore4.txt");
		break;	// 4x4
	}
	if (!fin.is_open())
	{
		cout << "File Not found \n\a";
		Sleep(2000);
		exit(EXIT_FAILURE);
	}
	else
	{
		fin >> highscore;
		fin.close();
	}
	data = new int*[rc];
	for (int i = 0; i < rc; i++)
	{
		data[i] = new int[rc];
	}		// created a two d array to hold the data
	SetAll(0);		// set every index to zero
	int counter = 0, y, z;
	while (counter < 2)				// generate TWO random number on first start
	{
		y = rand() % rc;				// to find a random index on the grid
		z = rand() % rc;
		int num;
		num = rand() % 20 + 1;			// to randomize the generation of 2 or 4 in the grid
		if (num % 2 == 0)			// if the num is even 
		{
			if (data[y][z] == 0)
			{
				data[y][z] = 2;
				counter++;
			}
			else							// 50-50 chance of a num being 2 or 4
				continue;
		}
		else
			if (num % 2 != 0)		// if the num is odd
			{
				if (data[y][z] == 0)
				{
					data[y][z] = 4;
					counter++;
				}
				else
					continue;
			}
	}
	ShowGrid();			// displays the grid and game starts
}
void Grid::Randomize()
{
	if (AvailableSpace())		// if the available space is zero, i.e. all indices are filled,
	{							// it can't and it won't randomize
		int counter = 0, y, z;
		while (counter < 1)				// generate one random number
		{
			y = rand() % rc;				// to find a random index on the grid
			z = rand() % rc;
			int num = rand() % 20;			// to randomize the generation of 2 or 4 in the grid
			if (num % 2 == 0)			// if the num is even 
			{
				if (data[y][z] == 0)
				{
					data[y][z] = 2;
					counter++;
				}
				else							// 50-50 chance of a num being 2 or 4
					continue;
			}
			else
				if (num % 2 != 0)		// if the num is odd
				{
					if (data[y][z] == 0)
					{
						data[y][z] = 4;
						counter++;
					}
					else
						continue;
				}
		}
	}
	else
		return;
}
void Grid::ShowGrid()
{
	cout << "\n\n\n\n\n";
	for (int i = 0; i < rc; i++)
	{
		for (int j = 0; j < rc; j++)
		{
			if (data[i][j])						// if there is any other value on the index other than zero it will print it,
				cout << "\t|  " << data[i][j];		// two spaces after the bar
			else
				cout << "\t|  " << "_";			// otherwise it will print a dash
		}
		if (i == 0)		// because we only gonna display the highscore and score once
		{
			if (score > highscore)
				highscore = score;
			cout << "\t\tHigh Score : " << highscore;
		}
		if (i == 1)						// score on the second line
			cout << "\t\tYour Score : " << score;
		cout << endl;
	}
}
void Grid::SetAll(int x) {

	for (int i = 0; i < rc; i++)
	{
		for (int j = 0; j < rc; j++)
		{
			data[i][j] = 0;
		}
	}
}
int Grid::AvailableSpace()
{
	int availableindices = 0;
	for (int i = 0; i < rc; i++)
	{
		for (int j = 0; j < rc; j++)
		{
			if (data[i][j] == 0)
			{
				return ++availableindices;
			}
		}
	}
	return availableindices;
}
bool Grid::Availability()
{
	if (!AvailableSpace())				// if all the boxes are full
	{
		for (int i = 0; i < rc; i++)
		{
			for (int j = 0; j < rc - 1; j++)
			{
				if (data[i][j] == data[i][j + 1])		// to check whether there are same numbers in a row
				{
					return true;
				}
				if (data[j][i] == data[j + 1][i])		// to check whether there are same numbers in a column
				{
					return true;
				}
			}
		}
	}
	else
		return true;		// true if there are empty boxes
	return false;
}
void Grid::Left()
{
	system("CLS");		// to clear the previous grid
	for (int i = 0; i < rc; i++)
	{
		if (rc == 3)		// 3x3
		{
			if (data[i][0] == 0)
			{
				if (data[i][1] == 0)				// 0 0 x
				{
					data[i][0] = data[i][2];
					data[i][2] = 0;
				}
				else
				{					// 0 x x
					if (data[i][1] == data[i][2])
					{
						data[i][0] = data[i][1] + data[i][2];
						score += data[i][0];
						data[i][1] = data[i][2] = 0;
					}
					else
					{				// 0 x y
						data[i][0] = data[i][1];
						data[i][1] = data[i][2];
						data[i][2] = 0;
					}
				}
			}
			else
			{
				if (data[i][1] == 0)
				{
					if (data[i][0] == data[i][2])			// x 0 x 
					{
						data[i][0] += data[i][2];
						score += data[i][0];
						data[i][1] = data[i][2] = 0;
					}
					else
					{			// x 0 y
						data[i][1] = data[i][2];
						data[i][2] = 0;
					}
				}
				else
				{
					if (data[i][0] == data[i][1])			// x x x
					{
						data[i][0] += data[i][1];
						score += data[i][0];
						data[i][1] = data[i][2];
						data[i][2] = 0;
					}
					else			// x y y
					{
						if (data[i][1] == data[i][2])
						{
							data[i][1] += data[i][2];
							score += data[i][1];
							data[i][2] = 0;
						}
						else
							continue;	// do nothing; all are different
					}
				}
			}
		} // **************************** 3x3 *************************//
		if (rc == 4)		// 4x4
		{
			if (data[i][0] == 0)
			{
				if (data[i][1] == 0)
				{
					if (data[i][2] == 0)			// 0 0 0 x
					{
						data[i][0] = data[i][3];
						data[i][3] = 0;
					}
					else
					{
						// 0 0 x x
						if (data[i][2] == data[i][3])
						{
							data[i][0] = data[i][2] + data[i][3];
							score += data[i][0];
							data[i][2] = data[i][3] = 0;
						}
						else
						{				// 0 0 x y
							data[i][0] = data[i][2];
							data[i][1] = data[i][3];
							data[i][2] = data[i][3] = 0;
						}
					}
				}
				else
				{
					if (data[i][2] == 0)
					{
						if (data[i][1] == data[i][3])			// 0 x 0 x 
						{
							data[i][0] = data[i][1] + data[i][3];
							score += data[i][0];
							data[i][1] = data[i][3] = 0;
						}
						else
						{			// 0 x 0 y
							data[i][0] = data[i][1];
							data[i][1] = data[i][3];
							data[i][1] = data[i][3] = 0;
						}
					}
					else
					{
						if (data[i][1] == data[i][2])			// 0 x x x
						{
							data[i][0] = data[i][1] + data[i][2];
							score += data[i][0];
							data[i][1] = data[i][3];
							data[i][2] = data[i][3] = 0;
						}
						else
						{			// 0 x y y
							if (data[i][2] == data[i][3])
							{
								data[i][0] = data[i][1];
								data[i][1] = data[i][2] + data[i][3];
								score += data[i][1];
								data[i][2] = data[i][3] = 0;
							}
							else
							{		// 0 x y x
								data[i][0] = data[i][1];
								data[i][1] = data[i][2];
								data[i][2] = data[i][3];
								data[i][3] = 0;
							}
						}
					}
				}
			}
			else
			{
				if (data[i][1] == 0)
				{
					if (data[i][2] == 0)
					{
						if (data[i][0] == data[i][3])			// x 0 0 x
						{
							data[i][0] += data[i][3];
							score += data[i][0];
							data[i][3] = 0;
						}
						else
						{				// x 0 0 y
							data[i][1] = data[i][3];
							data[i][3] = 0;
						}
					}
					else
					{				// x 0 x x
						if (data[i][0] == data[i][2])
						{
							data[i][0] += data[i][2];
							score += data[i][0];
							data[i][1] = data[i][3];
							data[i][2] = data[i][3] = 0;
						}
						else
						{				// x 0 y y
							if (data[i][2] == data[i][3])
							{
								data[i][1] = data[i][2] + data[i][3];
								score += data[i][1];
								data[i][2] = data[i][3] = 0;
							}
							else
							{				// x 0 y x 
								data[i][1] = data[i][2];
								data[i][2] = data[i][3];
								data[i][3] = 0;
							}
						}
					}
				}
				else
				{		// x x 0 x 
					if (data[i][2] == 0)
					{
						if (data[i][0] == data[i][1])
						{
							data[i][0] += data[i][1];
							score += data[i][0];
							data[i][1] = data[i][3];
							data[i][3] = 0;
						}
						else
						{			// x y 0 y
							if (data[i][1] == data[i][3])
							{
								data[i][1] += data[i][3];
								score += data[i][1];
								data[i][3] = 0;
							}
							else
							{				// x y 0 z
								data[i][2] = data[i][3];
								data[i][3] = 0;
							}
						}
					}
					else
					{
						if (data[i][0] == data[i][1])
						{
							if (data[i][2] == data[i][3])		// x x x x
							{
								data[i][0] += data[i][1];
								score += data[i][0];
								data[i][1] = data[i][2] + data[i][3];
								score += data[i][1];
								data[i][2] = data[i][3] = 0;
							}
							else
							{				// x x y x
								data[i][0] += data[i][1];
								score += data[i][0];
								data[i][1] = data[i][2];
								data[i][2] = data[i][3];
								data[i][3] = 0;
							}

						}
						else
						{				// x y y x
							if (data[i][1] == data[i][2])
							{
								data[i][1] += data[i][2];
								score += data[i][1];
								data[i][2] = data[i][3];
								data[i][3] = 0;
							}
							else
							{				// x y z z 
								if (data[i][2] == data[i][3])
								{
									data[i][2] += data[i][3];
									score += data[i][2];
									data[i][3] = 0;
								}
								else				// all are different
									continue;
							}

						}
					}
				}
			}
		}
	}	//end of column running for loop

}
void Grid::Right()
{
	system("CLS");		// to clear the previous grid
	for (int i = 0; i < rc; i++)
	{
		if (rc == 3)		// 3x3
		{
			if (data[i][2] == 0)
			{
				if (data[i][1] == 0)				// x 0 0
				{
					data[i][2] = data[i][0];
					data[i][0] = 0;
				}
				else
				{					// x x 0
					if (data[i][1] == data[i][0])
					{
						data[i][2] = data[i][0] + data[i][1];
						score += data[i][2];
						data[i][0] = data[i][1] = 0;
					}
					else
					{				// x y 0
						data[i][2] = data[i][1];
						data[i][1] = data[i][0];
						data[i][0] = 0;
					}
				}
			}
			else
			{
				if (data[i][1] == 0)
				{
					if (data[i][0] == data[i][2])			// x 0 x 
					{
						data[i][2] += data[i][0];
						score += data[i][2];
						data[i][0] = 0;
					}
					else
					{			// x 0 y
						data[i][1] = data[i][0];
						data[i][0] = 0;
					}
				}
				else
				{
					if (data[i][2] == data[i][1])			// x x x
					{
						data[i][2] += data[i][1];
						score += data[i][2];
						data[i][1] = data[i][0];
						data[i][0] = 0;
					}
					else			// y y x
					{
						if (data[i][1] == data[i][0])
						{
							data[i][1] += data[i][0];
							score += data[i][1];
							data[i][0] = 0;
						}
						else
							continue;	// do nothing; all are different
					}
				}
			}
		} // **************************** 3x3 *************************//
		if (rc == 4)		// 4x4
		{
			if (data[i][3] == 0)
			{
				if (data[i][2] == 0)
				{
					if (data[i][1] == 0)			// x 0 0 0
					{
						data[i][3] = data[i][0];
						data[i][0] = 0;
					}
					else
					{
						if (data[i][1] == data[i][0])		// x x 0 0 
						{
							data[i][3] = data[i][1] + data[i][0];
							score += data[i][3];
							data[i][1] = data[i][0] = 0;
						}
						else
						{				// x y 0 0
							data[i][3] = data[i][1];
							data[i][2] = data[i][0];
							data[i][0] = data[i][1] = 0;
						}
					}
				}
				else
				{
					if (data[i][1] == 0)
					{
						if (data[i][0] == data[i][2])			// x 0 x 0 
						{
							data[i][3] = data[i][2] + data[i][0];
							score += data[i][3];
							data[i][2] = data[i][0] = 0;
						}
						else
						{			// y 0 x 0
							data[i][3] = data[i][2];
							data[i][2] = data[i][0];
							data[i][1] = data[i][0] = 0;
						}
					}
					else
					{
						if (data[i][1] == data[i][2])			// x x x 0
						{
							data[i][3] = data[i][1] + data[i][2];
							score += data[i][3];
							data[i][2] = data[i][0];
							data[i][1] = data[i][0] = 0;
						}
						else
						{				// y y x 0
							if (data[i][0] == data[i][1])
							{
								data[i][3] = data[i][2];
								data[i][2] = data[i][1] + data[i][0];
								score += data[i][2];
								data[i][1] = data[i][0] = 0;
							}
							else {
								//  x y x 0
								data[i][3] = data[i][2];
								data[i][2] = data[i][1];
								data[i][1] = data[i][0];
								data[i][0] = 0;
							}
						}
					}
				}
			}
			else
			{
				if (data[i][2] == 0)
				{
					if (data[i][1] == 0)
					{
						if (data[i][3] == data[i][0])			// x 0 0 x
						{
							data[i][3] += data[i][0];
							score += data[i][3];
							data[i][0] = 0;
						}
						else
						{				// y 0 0 x
							data[i][2] = data[i][0];
							data[i][0] = 0;
						}
					}
					else
					{				// x x 0 x
						if (data[i][3] == data[i][1])
						{
							data[i][3] += data[i][1];
							score += data[i][3];
							data[i][2] = data[i][0];
							data[i][1] = data[i][0] = 0;
						}
						else
						{				// y y 0 x
							if (data[i][1] == data[i][0])
							{
								data[i][2] = data[i][1] + data[i][0];
								score += data[i][2];
								data[i][1] = data[i][0] = 0;
							}
							else
							{				// x y 0 x 
								data[i][2] = data[i][1];
								data[i][1] = data[i][0];
								data[i][0] = 0;
							}
						}
					}
				}
				else
				{
					if (data[i][1] == 0)
					{
						if (data[i][3] == data[i][2])	// x 0 x x 
						{
							data[i][3] += data[i][2];
							score += data[i][3];
							data[i][2] = data[i][0];
							data[i][0] = 0;
						}
						else
						{			// y 0 y x
							if (data[i][2] == data[i][0])
							{
								data[i][2] += data[i][0];
								score += data[i][2];
								data[i][0] = 0;
							}
							else
							{
								data[i][1] = data[i][0];
								data[i][0] = 0;
							}
						}
					}
					else
					{
						if (data[i][3] == data[i][2])
						{
							if (data[i][1] == data[i][0])		// x x x x
							{
								data[i][3] += data[i][2];
								score += data[i][3];
								data[i][2] = data[i][1] + data[i][0];
								score += data[i][2];
								data[i][1] = data[i][0] = 0;
							}
							else
							{				// x y x x
								data[i][3] += data[i][2];
								score += data[i][3];
								data[i][2] = data[i][1];
								data[i][1] = data[i][0];
								data[i][0] = 0;
							}

						}
						else
						{				// x y y x
							if (data[i][2] == data[i][1])
							{
								data[i][2] += data[i][1];
								score += data[i][2];
								data[i][1] = data[i][0];
								data[i][0] = 0;
							}
							else
							{				// z z y x  
								if (data[i][1] == data[i][0])
								{
									data[i][1] += data[i][0];
									score += data[i][1];
									data[i][0] = 0;
								}
								else				// all are different
									continue;
							}
						}
					}
				}
			}
		}
	}	//end of column running for loop
}
void Grid::Down()
{
	system("CLS");		// to clear the previous grid
	for (int i = 0; i < rc; i++)
	{
		if (rc == 3)		// 3x3
		{
			if (data[2][i] == 0)
			{
				if (data[1][i] == 0)			// x
				{								// 0	
					data[2][i] = data[0][i];	// 0
					data[0][i] = 0;
				}
				else
				{									// x
					if (data[1][i] == data[0][i])	// x
					{								// 0
						data[2][i] = data[0][i] + data[1][i];
						score += data[2][i];
						data[0][i] = data[1][i] = 0;
					}
					else
					{								// y
						data[2][i] = data[1][i];	// x	
						data[1][i] = data[0][i];	// 0
						data[0][i] = 0;
					}
				}
			}
			else
			{
				if (data[1][i] == 0)						// x
				{											// 0
					if (data[0][i] == data[2][i])			// x 
					{
						data[2][i] += data[0][i];
						score += data[2][i];
						data[0][i] = 0;
					}
					else
					{								// y
						data[1][i] = data[0][i];	// 0
						data[0][i] = 0;				// x
					}
				}
				else
				{
					if (data[2][i] == data[1][i])			// x
					{										// x
						data[2][i] += data[1][i];			// x
						score += data[2][i];
						data[1][i] = data[0][i];
						data[0][i] = 0;
					}
					else
					{
						if (data[1][i] == data[0][i])		// y
						{									// y
							data[1][i] += data[0][i];		// x
							score += data[1][i];
							data[0][i] = 0;
						}
						else
							continue;	// do nothing;	all are different
					}
				}
			}
		} // **************************** 3x3 *************************//
		if (rc == 4)		// 4x4
		{
			if (data[3][i] == 0)
			{
				if (data[2][i] == 0)
				{
					if (data[1][i] == 0)			// x 
					{								// 0
						data[3][i] = data[0][i];	// 0
						data[0][i] = 0;				// 0
					}
					else
					{
						if (data[1][i] == data[0][i])					// x 
						{												// x
							data[3][i] = data[1][i] + data[0][i];		// 0
							score += data[3][i];
							data[1][i] = data[0][i] = 0;				// 0
						}
						else
						{									// x 
							data[3][i] = data[1][i];		// y
							data[2][i] = data[0][i];		// 0
							data[0][i] = data[1][i] = 0;	// 0
						}
					}
				}
				else
				{
					if (data[1][i] == 0)
					{
						if (data[0][i] == data[2][i])				// x
						{											// 0
							data[3][i] = data[2][i] + data[0][i];	// x
							score += data[3][i];
							data[2][i] = data[0][i] = 0;			// 0
						}
						else
						{										// y 
							data[3][i] = data[2][i];			// 0
							data[2][i] = data[0][i];			// x
							data[0][i] = 0;						// 0
						}
					}
					else
					{
						if (data[1][i] == data[2][i])				// x 
						{											// x
							data[3][i] = data[1][i] + data[2][i];	// x
							score += data[3][i];
							data[2][i] = data[0][i];				// 0
							data[1][i] = data[0][i] = 0;
						}
						else
						{
							if (data[1][i] == data[0][i])				// y
							{											// y
								data[3][i] = data[2][i];				// x
								data[2][i] = data[1][i] + data[0][i];	// 0
								score += data[2][i];
								data[1][i] = data[0][i] = 0;
							}
							else
							{									// x
								data[3][i] = data[2][i];		// y
								data[2][i] = data[1][i];		// x
								data[1][i] = data[0][i];		// 0
								data[0][i] = 0;
							}
						}
					}
				}
			}
			else
			{
				if (data[2][i] == 0)
				{
					if (data[1][i] == 0)
					{
						if (data[3][i] == data[0][i])			// x
						{										// 0
							data[3][i] += data[0][i];			// 0
							score += data[3][i];
							data[0][i] = 0;						// x
						}
						else
						{									// y
							data[2][i] = data[0][i];		// 0
							data[0][i] = 0;					// 0
						}									// x
					}
					else
					{										// x
						if (data[3][i] == data[1][i])		// x
						{									// 0
							data[3][i] += data[1][i];		// x
							score += data[3][i];
							data[2][i] = data[0][i];
							data[1][i] = data[0][i] = 0;
						}
						else
						{												// y
							if (data[1][i] == data[0][i])				// y
							{											// 0
								data[2][i] = data[1][i] + data[0][i];	// x
								score += data[2][i];
								data[1][i] = data[0][i] = 0;
							}
							else
							{								// x 
								data[2][i] = data[1][i];	// y
								data[1][i] = data[0][i];	// 0
								data[0][i] = 0;				// x
							}
						}
					}
				}
				else
				{										// x 
					if (data[1][i] == 0)				// 0
					{									// x
						if (data[3][i] == data[2][i])	// x
						{
							data[3][i] += data[2][i];
							score += data[3][i];
							data[2][i] = data[0][i];
							data[0][i] = 0;
						}
						else
						{									// y
							if (data[2][i] == data[0][i])	// 0
							{								// y
								data[2][i] += data[0][i];	// x
								score += data[2][i];
								data[0][i] = 0;
							}
							else							// x
							{								// 0
								data[1][i] = data[0][i];	// y
								data[0][i] = 0;				// x
							}
						}
					}
					else
					{
						if (data[3][i] == data[2][i])
						{
							if (data[1][i] == data[0][i])				// x
							{											// x
								data[3][i] += data[2][i];				// x
								score += data[3][i];
								data[2][i] = data[1][i] + data[0][i];	// x
								score += data[2][i];
								data[1][i] = data[0][i] = 0;
							}
							else
							{								// x
								data[3][i] += data[2][i];	// y
								score += data[3][i];
								data[2][i] = data[1][i];	// x
								data[1][i] = data[0][i];	// x
								data[0][i] = 0;
							}

						}
						else
						{										// x
							if (data[2][i] == data[1][i])		// y
							{									// y
								data[2][i] += data[1][i];		// x
								score += data[2][i];
								data[1][i] = data[0][i];
								data[0][i] = 0;
							}
							else
							{									// z
								if (data[1][i] == data[0][i])	// z
								{								// y
									data[1][i] += data[0][i];	// x
									score += data[1][i];
									data[0][i] = 0;
								}
								else				// all are different
									continue;
							}
						}
					}
				}
			}
		}
	}	//end of column running for loop
}
void Grid::Up()
{
	system("CLS");		// to clear the previous grid
	for (int i = 0; i < rc; i++)
	{
		if (rc == 3)		// 3x3
		{
			if (data[0][i] == 0)
			{
				if (data[1][i] == 0)				// 0
				{									// 0
					data[0][i] = data[2][i];		// x
					data[2][i] = 0;
				}
				else
				{												// 0
					if (data[1][i] == data[2][i])				// x
					{											// x
						data[0][i] = data[1][i] + data[2][i];
						score += data[0][i];
						data[1][i] = data[2][i] = 0;
					}
					else
					{								// 0
						data[0][i] = data[1][i];	// x
						data[1][i] = data[2][i];	// y
						data[2][i] = 0;
					}
				}
			}
			else
			{
				if (data[1][i] == 0)
				{
					if (data[0][i] == data[2][i])			// x 
					{										// 0
						data[0][i] += data[2][i];			// x
						score += data[0][i];
						data[1][i] = data[2][i] = 0;
					}
					else
					{								// x
						data[1][i] = data[2][i];	// 0
						data[2][i] = 0;				// y
					}
				}
				else
				{
					if (data[0][i] == data[1][i])			// x
					{										// x
						data[0][i] += data[1][i];			// x
						score += data[0][i];
						data[1][i] = data[2][i];
						data[2][i] = 0;
					}
					else									// x
					{										// y
						if (data[1][i] == data[2][i])		// y
						{
							data[1][i] += data[2][i];
							score += data[1][i];
							data[2][i] = 0;
						}
						else
							continue;	// do nothing; all are different
					}
				}
			}
		} // **************************** 3x3 *************************//
		if (rc == 4)		// 4x4
		{
			if (data[0][i] == 0)
			{
				if (data[1][i] == 0)
				{
					if (data[2][i] == 0)			// 0
					{								// 0
						data[0][i] = data[3][i];	// 0
						data[3][i] = 0;				// x
					}
					else
					{												// 0
						if (data[2][i] == data[3][i])				// 0
						{											// x
							data[0][i] = data[2][i] + data[3][i];	// x
							score += data[0][i];
							data[2][i] = data[3][i] = 0;
						}
						else
						{									// 0
							data[0][i] = data[2][i];		// 0
							data[1][i] = data[3][i];		// y
							data[2][i] = data[3][i] = 0;	// x
						}
					}
				}
				else
				{
					if (data[2][i] == 0)
					{
						if (data[1][i] == data[3][i])				// 0 
						{											// x
							data[0][i] = data[1][i] + data[3][i];	// 0
							score += data[0][i];
							data[1][i] = data[3][i] = 0;			// x
						}
						else
						{									// 0
							data[0][i] = data[1][i];		// x
							data[1][i] = data[3][i];		// 0
							data[1][i] = data[3][i] = 0;	// y
						}
					}
					else
					{
						if (data[1][i] == data[2][i])					// 0
						{												// x
							data[0][i] = data[1][i] + data[2][i];		// x
							score += data[0][i];
							data[1][i] = data[3][i];					// x
							data[2][i] = data[3][i] = 0;
						}
						else
						{												// 0
							if (data[2][i] == data[3][i])				// x
							{											// y
								data[0][i] = data[1][i];				// y
								data[1][i] = data[2][i] + data[3][i];
								score += data[1][i];
								data[2][i] = data[3][i] = 0;
							}
							else
							{									// 0
								data[0][i] = data[1][i];		// x
								data[1][i] = data[2][i];		// y
								data[2][i] = data[3][i];		// x
								data[3][i] = 0;
							}
						}
					}
				}
			}
			else
			{
				if (data[1][i] == 0)
				{
					if (data[2][i] == 0)
					{
						if (data[0][i] == data[3][i])			// x
						{										// 0
							data[0][i] += data[3][i];			// 0
							score += data[0][i];
							data[3][i] = 0;						// x
						}
						else
						{									// x
							data[1][i] = data[3][i];		// 0
							data[3][i] = 0;					// 0
						}									// y
					}
					else
					{										// x
						if (data[0][i] == data[2][i])		// 0
						{									// x
							data[0][i] += data[2][i];		// x
							score += data[0][i];
							data[1][i] = data[3][i];
							data[2][i] = data[3][i] = 0;
						}
						else
						{												// x
							if (data[2][i] == data[3][i])				// 0
							{											// y
								data[1][i] = data[2][i] + data[3][i];	// y
								score += data[1][i];
								data[2][i] = data[3][i] = 0;
							}
							else
							{									// x 
								data[1][i] = data[2][i];		// 0
								data[2][i] = data[3][i];		// y
								data[3][i] = 0;					// x
							}
						}
					}
				}
				else
				{
					if (data[2][i] == 0)
					{
						if (data[0][i] == data[1][i])	// x
						{								// x
							data[0][i] += data[1][i];	// 0
							score += data[0][i];
							data[1][i] = data[3][i];	// x
							data[3][i] = 0;
						}
						else
						{									// x
							if (data[1][i] == data[3][i])	// y
							{								// 0
								data[1][i] += data[3][i];	// y
								score += data[1][i];
								data[3][i] = 0;
							}
							else
							{								// x
								data[2][i] = data[3][i];	// y
								data[3][i] = 0;				// 0
							}								// z
						}
					}
					else
					{
						if (data[0][i] == data[1][i])
						{
							if (data[2][i] == data[3][i])				// x
							{											// x
								data[0][i] += data[1][i];				// x
								score += data[0][i];
								data[1][i] = data[2][i] + data[3][i];	// x
								score += data[1][i];
								data[2][i] = data[3][i] = 0;
							}
							else
							{								// x
								data[0][i] += data[1][i];	// x
								score += data[0][i];
								data[1][i] = data[2][i];	// y
								data[2][i] = data[3][i];	// x
								data[3][i] = 0;
							}
						}
						else
						{										// x
							if (data[1][i] == data[2][i])		// y
							{									// y
								data[1][i] += data[2][i];		// x
								score += data[1][i];
								data[2][i] = data[3][i];
								data[3][i] = 0;
							}
							else
							{									// x 
								if (data[2][i] == data[3][i])	// y
								{								// z
									data[2][i] += data[3][i];	// z
									score += data[2][i];
									data[3][i] = 0;
								}
								else				// all are different
									continue;
							}
						}
					}
				}
			}
		}
	}	//end of column running for loop
}
void Grid::Save()
{
	ofstream fout;
	if (rc == 3)
		fout.open("highscore3.txt");
	if (rc == 4)
		fout.open("highscore4.txt");
	if (!fout.is_open())
	{
		cout << "File Not found!\a\n";
		Sleep(2000);
		exit(EXIT_SUCCESS);
	}
	else
	{
		fout << highscore;
		fout.close();
	}
}
ofstream& operator<<(ofstream& fout, Grid& g)
{
	fout << g.score << endl;
	for (int i = 0; i < g.rc; i++)
	{
		for (int j = 0; j < g.rc; j++)
		{
			if (g.data[i][j] == 0)
			{
				fout << "\t" << setw(5) << "_";
				continue;
			}
			fout << "\t" << setw(5) << g.data[i][j];
		}
		fout << endl;
	}
	return fout;
}
Grid::~Grid()
{
	delete[] data;
}