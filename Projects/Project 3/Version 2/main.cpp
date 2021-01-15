//File main.cpp
//Javier Pastor Ramirez

#include <iostream>
using namespace std;
#include "senku.h"


int main() {
	bool correct;
	int option; //For the menu
	tGame game;

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

			};

		} while (option != 0);
	}

	save(game, name);

	return 0;
}