//File main.cpp
//Javier Pastor Ramirez

#include <iostream>
using namespace std;
#include "senku.h"


int main() {
	bool correct;
	tGame game;

	correct = load(game, name);

	if (correct){

		cout << "Correctly loaded" << endl << endl << endl;

		show(game);
		save(game, name);
	}

	cout << endl << endl << endl;

	system("pause");
	return 0;
}


//Black = 0
//Green = 2
//Light Green = 10
//White = 15