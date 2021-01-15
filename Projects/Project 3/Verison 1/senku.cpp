//File senku.cpp

#include <iostream>
using namespace std;
#include "senku.h"

//////////////
//Prototypes//
//////////////

//File
bool load(tGame &game, const string &name); //I suppose the parameter name is given somewhere
void save(const tGame &game, const string &name);

//Display
void show(const tGame &game);

//Type conversion
tCell intToCell(int number);

//Terminal color
void backgroundColor(int color);

//////////////////
//Implementation//
//////////////////

//File
bool load(tGame &game, const string &name) {
	bool correct = false;
	int size; //To get the size of the matrix
	int auxiliar; //To get the matrix from the file
	ifstream file;

	file.open(name);
	if (file.is_open()){
		correct = true;
		
		file >> size;
		//file >> DIM; //Where do I have to store the size? Can I declare an array of this dimension or o i use the maximun array size?
		file >> game.initialPegs >> game.rowGoal >> game.columnGoal;

		for (int i = 0; i < size; i++){ //To get the matrix from the file
			for (int j = 0; j < size; j++){
				file >> auxiliar;
				game.matrix[i][j] = intToCell(auxiliar);
			}
		}

		file >> game.movements;

		file.close();
	}

	return correct;
}

void save(const tGame &game, const string &name){ //Check DIM problem
	ofstream file;

	file.open(name);
	if (file.is_open()){

		file << DIM << endl; //The dimension must be stored in tGame or be a variable constant

		file << game.initialPegs << endl << game.rowGoal << endl << game.columnGoal << endl;

		for (int i = 0; i < DIM; i++){
			for (int j = 0; j < DIM; j++){
				file << game.matrix[i][j] << " ";
			}
			file << endl;
		}

		file << game.movements;

		file.close();
	}

}

//Display
void show(const tGame &game){

	for (int i = 0; i < DIM; i++){

		if (i == 0){
			cout << "       ";
			for (int k = 0; k < DIM; k++)
				cout << k + 1 << " ";
			cout << endl;
		}

		for (int j = 0; j < DIM; j++){
			
			if (j == 0)
				cout << "    " << setw(2) << left << i + 1 << " ";

			if ((i == game.rowGoal) && (j == game.columnGoal)){
				backgroundColor(10);
				cout << char(254);
				backgroundColor(0);
			}
			else if (game.matrix[i][j] == 0)
				backgroundColor(0);
			else if (game.matrix[i][j] == 2)
				backgroundColor(2);
			else if (game.matrix[i][j] == 10)
				backgroundColor(10);

			cout << " ";

			backgroundColor(0);

			cout << " ";

		}

		cout << endl << endl;
	}

}

//Type conversion
tCell intToCell(int number){
	tCell cell;

	if (number == 0)
		cell = UNAV;
	else if (number == 2)
		cell = EMPTY;
	else if (number == 10)
		cell = PEG;

	return cell;
}

//Terminal color
void backgroundColor(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
} //Revise