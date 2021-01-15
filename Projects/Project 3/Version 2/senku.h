//File senku.h

#include <string>
#include <fstream>
#include <windows.h>
using namespace std;
#include <iomanip>
#include <ctime>

////////////////////
//Global Constants//
////////////////////
const int DIM = 6; //For the dimensions of the matrix (The maximum value)
const int NUM_DIRS = 4; //For the number of possible directions
const string name = "board.txt";

//////////////////////
//Arrays and Structs//
//////////////////////

typedef enum tCell { UNAV = 0, EMPTY = 2, PEG = 10 }; //For the type of the cell
typedef enum tState { DEADLOCK, WON, PLAYING, ABANDONED }; //For the status of the game
typedef enum tMovements { UP, DOWN, LEFT, RIGHT, WRONG }; //For the possible moves of the peg

typedef bool tPossibles[NUM_DIRS]; //Up, down, left, right

typedef tCell tMatrix[DIM][DIM]; //Row - Column

typedef int tIndexNewCells[DIM * DIM][1]; //For the random board generation

typedef struct {

	tIndexNewCells indexNewCells;
	int counter;

} tNewCells;

typedef struct {

	tMatrix matrix;
	int rowGoal;
	int columnGoal;
	int initialPegs;
	int moveCounter;
	tState state;

} tGame;

typedef struct {

	int row;
	int column;
	tMovements movements;

} tMove;


//////////////
//Prototypes//
//////////////

//Menu
int menu();

//File
bool load(tGame &game, const string &name);

void save(const tGame &game, const string &name);

//Display
void show(const tGame &game);

void displayMovements(tPossibles possibles);

//Type conversion
tCell intToCell(int number);

tMovements charToMovement(char character);

//Terminal color
void backgroundColor(int color);

//Input
bool askForPeg(tMove &moves, tGame game);

tMovements playerMovement(tPossibles possibles);

//Check valid moves
bool validMoves(tPossibles &possibles, int row, int column, tGame game);

bool possibleMove(tPossibles possibles, tMovements move);

void any_Peg_can_Move(tGame &game);

//Runs the game
void match(tGame &game);

void executeMove(tGame &game, tMove moves);

//Check Peg
bool checkPeg(tGame game, int row, int column);

//Random board generation
void generateBoard(tGame &game, int moves);

void initBoard(tMatrix matrix);

void setGoal(tGame &game);

bool inverseMove(tGame &game);