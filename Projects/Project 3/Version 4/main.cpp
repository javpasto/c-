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
	bool boardExits = false;
	string name;
	tLastMoves lastMoves;

	initLastMove(lastMoves);

	do {
		option = menu();

		switch (option)
		{
		case 1:
			name = fileToLoad();
			boardExits = load(game, name, lastMoves);
			if (boardExits == false)
				boardExits = load(game, "default.txt", lastMoves);
			if (boardExits == false)
				cout << "Unable to load any file." << endl << endl;
			break;

		case 2:
			if (boardExits == false){
				cout << "Default board will be loaded" << endl << endl;
				boardExits = load(game, "default.txt", lastMoves);
			}

			if (boardExits == true){
				match(game, lastMoves);
				initLastMove(lastMoves); //Initialice the array at the end of each match
			}

			if (boardExits == false)
				cout << "Unable to load default board." << endl << endl;

			break;

		case 3:
				
			cout << "Give me the number of moves you want me to make: ";
			cin >> moves;

			cout << endl << endl << endl;

			generateBoard(game, moves, lastMoves);

			boardExits = true;

			break;
		};

	} while (option != 0);

	return 0;
}