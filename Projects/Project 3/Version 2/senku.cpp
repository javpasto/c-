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

	for (int i = 0; i < NUM_DIRS; i++)
		possibles[i] = false;

	if (row - 2 < DIM) //Move up
		if (game.matrix[row - 2][column] == EMPTY)
			if (game.matrix[row - 1][column] == PEG)
				possibles[0] = true;

	if (row + 2 < DIM) //Move down
		if (game.matrix[row + 2][column] == EMPTY)
			if (game.matrix[row + 1][column] == PEG)
				possibles[1] = true;

	if (column - 2 < DIM) //Move left
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
			cout << "You have done " << game.moveCounter << " on this board. See you soon!" << endl;
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
void generateBoard(tGame &game, int moves){
	bool generateMore = true;
	tNewCells newCells;

	srand(time(NULL));

	setGoal(game);

	newCells.counter = 0;

	newCells.indexNewCells[game.rowGoal][0] = game.rowGoal;
	newCells.indexNewCells[game.columnGoal][1] = game.columnGoal;

	while ((newCells.counter < moves) && (generateMore)){
		
		generateMore = inverseMove(game);

		newCells.counter++;
	}

	game.initialPegs = newCells.counter;
}

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

bool inverseMove(tGame &game){
	bool correct = true;



	return correct;
}