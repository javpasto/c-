//File senku.cpp

#include <iostream>
using namespace std;
#include "senku.h"


//////////////////
//Implementation//
//////////////////

//Menu
int menu(){
	int option;

	do {

		cout << "1 - Play Match" << endl
			<< "2 - Generate Random Board" << endl
			<< "0 - Exit" << endl
			<< "Your option: ";

		cin >> option;

	} while ((option < 0) || (option > 2));

	cout << endl;

	return option;
}

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

		file >> game.moveCounter;

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

		file << game.moveCounter;

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
				if (game.matrix[game.rowGoal][game.columnGoal] == PEG)
					backgroundColor(10);
				else
					backgroundColor(2);

				cout << char(254);

				backgroundColor(0);
			}
			else if (game.matrix[i][j] == UNAV){
				backgroundColor(0);
				cout << " ";
			}
			else if (game.matrix[i][j] == EMPTY){
				backgroundColor(2);
				cout << " ";
			}
			else if (game.matrix[i][j] == PEG){
				backgroundColor(10);
				cout << " ";
			}

			backgroundColor(0);

			cout << " ";

		}

		cout << endl << endl;
	}

}

void displayMovements(tPossibles possibles){

	cout << "Select direction:" << endl;

	if (possibles[0])
		cout << "        [U]p" << endl;
	if (possibles[1])
		cout << "        [D]own" << endl;
	if (possibles[2])
		cout << "        [L]eft" << endl;
	if (possibles[3])
		cout << "        [R]ight" << endl;

	cout << "        [S]elect another peg" << endl << endl << endl;

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

tMovements charToMovement(char character){
	tMovements move = WRONG;

	if (character == 'U')
		move = UP;
	else if (character == 'D')
		move = DOWN;
	else if (character == 'L')
		move = LEFT;
	else if (character == 'R')
		move = RIGHT;

	return move;
}

//Terminal color
void backgroundColor(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));

	//Colors for terminal
	//Black = 0
	//Green = 2
	//Light Green = 10
	//White = 15

} //Revise

//Input
bool askForPeg(tMove &moves, tGame game){
	bool correct;
	bool anyMove = true;
	tPossibles possibles;

	do{
		cout << "Please select PEG (row and column), or 0 to exit: " << endl
			<<"Row: ";
		cin >> moves.row;

		cout << "Column: ";
		cin >> moves.column;
		
		if ((moves.row == 0) || (moves.column == 0)){
			anyMove = false;
			correct = true;
		}
		else
			correct = checkPeg(game, moves.row, moves.column);

	} while (!correct);

	if (anyMove == true) {

		moves.column--;
		moves.row--;

		anyMove = validMoves(possibles, moves.row, moves.column, game);

		if (anyMove == true) {
			moves.movements = playerMovement(possibles);
		}

	}

	return anyMove;
}

tMovements playerMovement(tPossibles possibles){
	tMovements move = WRONG;
	char auxiliar;
	bool correct = false;

	displayMovements(possibles);

	do {

		cin >> auxiliar;

		auxiliar = toupper(auxiliar);

		move = charToMovement(auxiliar);

		correct = possibleMove(possibles, move);

	} while ((!correct) && (move != WRONG));

	return move;
}

//Check valid moves
bool validMoves(tPossibles &possibles, int row, int column, tGame game){
	bool anyMovement = false;

	initPossibles(possibles);

	if (row - 2 >= 0) //Move up
		if (game.matrix[row - 2][column] == EMPTY)
			if (game.matrix[row - 1][column] == PEG)
				possibles[0] = true;

	if (row + 2 < DIM) //Move down
		if (game.matrix[row + 2][column] == EMPTY)
			if (game.matrix[row + 1][column] == PEG)
				possibles[1] = true;

	if (column - 2 >= 0) //Move left
		if (game.matrix[row][column - 2] == EMPTY)
			if (game.matrix[row][column - 1] == PEG)
				possibles[2] = true;

	if (column + 2 < DIM) //Move right
		if (game.matrix[row][column + 2] == EMPTY)
			if (game.matrix[row][column + 1] == PEG)
				possibles[3] = true;

	for (int i = 0; i < NUM_DIRS; i++)
		if (possibles[i] == true)
			anyMovement = true;

	return anyMovement;
}

bool possibleMove(tPossibles possibles, tMovements move){
	bool correct = false;

	if (move == UP)
		if (possibles[0] == true)
			correct = true;
	if (move == DOWN)
		if (possibles[1] == true)
			correct = true;
	if (move == LEFT)
		if (possibles[2] == true)
			correct = true;
	if (move == RIGHT)
		if (possibles[3] == true)
			correct = true;

	return correct;
}

void any_Peg_can_Move(tGame &game){
	tPossibles possibles;
	bool auxiliar, anyPeg = false;
	int i = 0, j = 0, counter = 0, row, column;

	while (i < DIM) {
		while (j < DIM) {
			if (game.matrix[i][j] == PEG){

				auxiliar = validMoves(possibles, i, j, game);
				if (auxiliar == true)
					anyPeg = true;

				counter++;
				row = i;
				column = j;
			}
			j++;
		}

		j = 0;
		i++;
	}

	if (!anyPeg){

		game.state = DEADLOCK;

		if (counter == 1){ //Only enters the loop if there is just one peg
			if ((row == game.rowGoal) && (column == game.columnGoal))
				game.state = WON; //If the peg is in the Goal
		}
	}

}

//Runs the game
void match(tGame &game){
	tMove moves;
	bool correct;
	tMovements finalMove;

	game.state = PLAYING;

	show(game);

	do {

		correct = askForPeg(moves, game); //Equal to some boolean

		if (correct) {

			executeMove(game, moves);
			system("cls");
			show(game);

		}

		if ((moves.row == 0) || (moves.column == 0))
			game.state = ABANDONED;
		else
			any_Peg_can_Move(game);

		if (game.state == WON){
			cout << "You won the game!" << endl;
			system("pause");
		}
		else if (game.state == DEADLOCK){
			cout << "You can not move more Pegs." << endl;
			system("pause");
		}
		else if (game.state == ABANDONED){
			cout << "You have done " << game.moveCounter << " movements on this board. See you soon!" << endl;
			system("pause");
		}

	} while (game.state == PLAYING);

}

void executeMove(tGame &game, tMove moves){

	if (moves.movements == UP){
		game.matrix[moves.row][moves.column] = EMPTY;
		game.matrix[moves.row - 1][moves.column] = EMPTY;
		game.matrix[moves.row - 2][moves.column] = PEG;
	}
	else if (moves.movements == DOWN){
		game.matrix[moves.row][moves.column] = EMPTY;
		game.matrix[moves.row + 1][moves.column] = EMPTY;
		game.matrix[moves.row + 2][moves.column] = PEG;
	}
	else if (moves.movements == LEFT){
		game.matrix[moves.row][moves.column] = EMPTY;
		game.matrix[moves.row][moves.column - 1] = EMPTY;
		game.matrix[moves.row][moves.column - 2] = PEG;
	}
	else if (moves.movements == RIGHT){
		game.matrix[moves.row][moves.column] = EMPTY;
		game.matrix[moves.row][moves.column + 1] = EMPTY;
		game.matrix[moves.row][moves.column + 2] = PEG;
	}

	if (moves.movements != WRONG)
		game.moveCounter++;

}

//Check Peg
bool checkPeg(tGame game, int row, int column){
	bool correct = true;

	if ((row > DIM) || (row < 0) || (column > DIM) || (column < 0) || (game.matrix[row - 1][column - 1] != PEG))
		correct = false;

	return correct;
}

//Random board generation
void initBoard(tMatrix matrix){

	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			matrix[i][j] = UNAV;

}

void setGoal(tGame &game){

	game.rowGoal = (rand() % DIM);
	game.columnGoal = (rand() % DIM);

	game.matrix[game.rowGoal][game.columnGoal] = PEG;

}

void generateBoard(tGame &game, int moves){
	bool generateMore = true;

	srand(time(NULL));

	initBoard(game.matrix);

	setGoal(game);

	game.initialPegs = 1;

	show(game);

	while ((game.initialPegs - 1 < moves) && (generateMore)){
		
		generateMore = inverseMove(game);

		if (generateMore){
			game.initialPegs++;
			show(game);
		}
	}

	cout << endl << endl << "Number of moves: " << game.initialPegs - 1 << endl;

	if (game.initialPegs - 1 < moves)
		cout << "No more inversed moves could be done.";

	cout << endl << endl << endl;

}

bool inverseMove(tGame &game){
	tPossibles possibles;
	tRepeatedRandom repeatedRandom;
	bool correct = true, repeated = false;
	int randomCell = 0, row, column, finalMove, counter = 0, randomNum = 0;

	initRepeatedRandom(repeatedRandom);

	do {

		if (game.initialPegs > 1)
			randomCell = (rand() % (game.initialPegs - 1));

		repeatedRandom[counter] = randomCell;

		seachCell(game, row, column, randomCell);

		correct = validInverseMoves(possibles, game, row, column);

		if (randomNum == game.initialPegs){ //No more pegs can be moved
			repeated = true;
			correct = true;
		}

		randomNum = numRepeatedRandom(repeatedRandom);

		counter++;

	} while (!correct);

	if (!repeated){

		do {

			finalMove = (rand() % NUM_DIRS);

		} while (possibles[finalMove] == false);

		executeInverseMove(game, finalMove, row, column);

	}

	if (repeated)
		correct = false;

	return correct;
}

void executeInverseMove(tGame &game, int number, int row, int column){

	if (number == 0) { //UP
		game.matrix[row][column] = EMPTY;
		game.matrix[row - 1][column] = PEG;
		game.matrix[row - 2][column] = PEG;
	}
	else if (number == 1) { //DOWN
		game.matrix[row][column] = EMPTY;
		game.matrix[row + 1][column] = PEG;
		game.matrix[row + 2][column] = PEG;
	}
	else if (number == 2) { //LEFT
		game.matrix[row][column] = EMPTY;
		game.matrix[row][column - 1] = PEG;
		game.matrix[row][column - 2] = PEG;
	}
	else if (number == 3) { //RIGHT
		game.matrix[row][column] = EMPTY;
		game.matrix[row][column + 1] = PEG;
		game.matrix[row][column + 2] = PEG;
	}

}

bool validInverseMoves(tPossibles &possibles, tGame game, int row, int column){
	bool anyMove = false;

	initPossibles(possibles);

	if (row - 2 >= 0) //UP
		if ((game.matrix[row - 1][column] != PEG) && (game.matrix[row - 2][column] != PEG))
			possibles[0] = true;
	if (row + 2 < DIM) //DOWN
		if ((game.matrix[row + 1][column] != PEG) && (game.matrix[row + 2][column] != PEG))
			possibles[1] = true;
	if (column - 2 >= 0) //LEFT
		if ((game.matrix[row][column - 1] != PEG) && (game.matrix[row][column - 2] != PEG))
			possibles[2] = true;
	if (column + 2 < DIM) //RIGHT
		if ((game.matrix[row][column + 1] != PEG) && (game.matrix[row][column + 2] != PEG))
			possibles[3] = true;

	for (int i = 0; i < NUM_DIRS; i++)
		if (possibles[i] == true)
			anyMove = true;

	return anyMove;
}

//Search Cell
void seachCell(tGame game, int &row, int &column, int randomCell){
	bool found = false;
	int i = 0, j = 0, counter = 0;

	while ((i < DIM) && !found){
		while ((j < DIM) && !found){
			if (game.matrix[i][j] == PEG){
				if (randomCell == counter){
					row = i;
					column = j;
					found = true;
				}

				counter++;
			}

			j++;

		}

		j = 0;
		i++;
	}
}

//Initialate array
void initPossibles(tPossibles possibles){

	for (int i = 0; i < NUM_DIRS; i++)
		possibles[i] = false;

}

void initRepeatedRandom(tRepeatedRandom repeatedRandom){

	for (int i = 0; i < DIM * DIM; i++)
		repeatedRandom[i] = -1;

}

//Count repeated randoms
int numRepeatedRandom(tRepeatedRandom repeatedRandom){
	int counter = 0;

	for (int i = 0; i < DIM * DIM; i++)
		if (repeatedRandom[i] >= 0)
			counter++;

	return counter;
}