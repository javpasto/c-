//File main.cpp
//Javier Pastor Ramirez

#include <iostream>
using namespace std;
#include "senku.h"


int main() {
	bool correct;
	int option; //For the menu
	tGame game;
	int moves; //for the random board

	correct = load(game, name);

	if (correct){
		do {
			option = menu();

			switch (option)
			{
			case 1:
				match(game);
				break;

			case 2:
				
				cout << "Give me the number of moves you want me to make: ";
				cin >> moves;

				cout << endl << endl << endl;

				generateBoard(game, moves);

				break;
			};

		} while (option != 0);
	}

	save(game, name);

	return 0;
}