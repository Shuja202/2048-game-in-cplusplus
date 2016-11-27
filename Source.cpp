#include<iostream>
#include<conio.h>
#include<fstream>
#include<iomanip>				// to use setw
#include<Windows.h>			// to use Sleep
#include<time.h>
using namespace std;
#include"Grid.h"
#undef max

int Menu();			// displays the menu and returns the choice as an rvalue(temporary) integer
int main()
{
	system("color 80");		// first digit background, second digit foreground
	time_t srand(time(NULL));			// seeding rand()
	int x;
Begining:	x = Menu();
	Grid g(x);		// created the grid of user's choice
	ofstream fout;
	if (x == 1)
		fout.open("grid3.txt");
	else
		if (x == 2)
			fout.open("grid4.txt");
	if (!fout.is_open())
	{
		cout << "\tCould not open File\a\n\n\tExiting Game!";
		Sleep(2000);
		exit(EXIT_FAILURE);
	}
	else
	{
		char move, skip;
		do
		{
			fout << g;		// store the current grid in the file
			if (GetAsyncKeyState(VK_ESCAPE))		// if the user pressed escape key
			{
				char choice;
				system("cls");		// to clear the menu
				cout << "\n\n\n\n\t\t\t\tQuit Game\n\t\t\t\tY/N\n";
				do {
					choice = _getch();
					if (choice == 'Y' || choice == 'y')
					{
						fout.close();
						g.~Grid();
						exit(EXIT_SUCCESS);
					}
					else
						if (choice == 'N' || choice == 'n')
						{
							system("cls");
							g.ShowGrid();
							break;		// break and ask for the next direction input
						}
				} while (true);
			}
			skip = _getch();	// just needed an extra variable to access the real ascii of arrow keys
			move = _getch();
			switch (move)
			{
			case 'H': 	g.Up(); break;
			case 'P':	g.Down(); break;
			case 'M':	g.Right(); break;
			case 'K':	g.Left(); break;
			default:
				continue;
			}
			g.Randomize();
			g.ShowGrid();
			if (!g.Availability())		// after every move check to see if game over 
			{
				char choice;
				cout << endl << "*************************// \tGAME OVER\t //*************************";
				g.Save();
				cout << endl << "\n\n\t\t\t Try Again\t\t\t\n\t\t\t  Y/N\n";
				do
				{
					choice = _getch();
					if (tolower(choice) == 'n')
					{
						fout.close();
						g.~Grid();
						exit(EXIT_SUCCESS);
					}
					else
					{
						if (tolower(choice) == 'y')
						{
							fout.close();				// to close the file which will be opened again after begining
							system("cls");
							goto Begining;		// starting the game again
						}
					}
				} while (true);
			}
		} while (true);
	}
	return 0;
}
int Menu()
{
	cout << "***************************************//////////\t2048\t//////////****************************************\n";
	cout << "\n\tUse Arrow Keys to move the numbers\n\tEcs  Quit\n";
	cout << "\nchose a grid: - \n1)\t 3x3\n2)\t 4x4\n";
	int gridchoice;
	do {
		cin >> gridchoice;
	} while (gridchoice != 1 && gridchoice != 2);
	system("cls");			// clear the menu
	return gridchoice;
}