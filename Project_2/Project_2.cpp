// Project_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
//////For Memory leaks
#include <Windows.h>
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
/////////////////////
#include "Game.h"




int main()
{
	// Checking for memory leaks.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);
	
	Game game;

	cout << "Loading dictionary..." << endl;
	game.LoadDictionary();

	game.LoadArrayUpWithSavedValues();

	game.hashTable.printSomeStuff();

	int choice;
	while (game._play)
	{
		system("cls");
		cout << "Welcome to the Jumble Game" << endl;
		cout << endl;
		cout << "1. Play" << endl;
		cout << "2. View high scores" << endl;
		cout << "3. Quit" << endl;
		cout << endl;
		cout << "choice? ";
		cin >> choice;


		if (cin.good())
		{

			if (choice < 1 || choice > 3)
			{
				cout << "Please choose a correct number choice." << endl;
				cout << endl;
				system("pause");
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				continue;
			}
			if (choice == 3)
			{
				Sleep(10);
				cout << endl;
				cout << "GoodBye!" << endl;
				cout << endl;
				game._play = false;
			}
			else if (choice == 2)
			{
				game.ReadInHighScores();
				system("pause");
				continue;
			}
			else if (choice == 1)
			{
				Sleep(20);
				game.BeginGuessing();
				continue;
			}
			break;
		}

		
		cout << "Please choose a correct number choice." << endl;
		cout << endl;
		system("pause");
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		Sleep(20);
		
	}

	
	
	if (choice != 3)
	{
		cout << endl;
		cout << "GoodBye!" << endl;
		cout << endl;
	}
	
	
};


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
