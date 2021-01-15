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
const int DIM = 20; //For the dimensions of the matrix
const int NUM_DIRS = 4; //For the number of possible directions
const int N = 5; //Number of inverse movements


//////////////////////
//Arrays and Structs//
//////////////////////

typedef enum tCell { UNAV = 0, EMPTY = 2, PEG = 10 }; //For the type of the cell
typedef enum tState { DEADLOCK, WON, PLAYING, ABANDONED }; //For the status of the game
typedef enum tMovements { UP, DOWN, LEFT, RIGHT, WRONG }; //For the possible moves of the peg

typedef bool tPossibles[NUM_DIRS]; //Up, down, left, right

typedef tCell tMatrix[DIM][DIM]; //Row - Column

typedef int tRepeatedRandom[DIM * DIM]; //For the random board

typedef struct {

	tMatrix matrix; //Board
	int rowGoal;
	int columnGoal;
	int initialPegs; //Never used
	int moveCounter; //Never used
	tState state;

} tGame;

typedef struct {

	int row;
	int column;
	tMovements movements;

} tMove; //Data for the peg movement

//Last Movements
typedef struct {

	int pegRow;
	int pegColumn;
	tMovements movement;

} tDataLastMove; //Save information of peg movement

typedef tDataLastMove tLastMoves[N]; //Last N Movements


//////////////
//Prototypes//
//////////////

//Menu
int menu();

//File
bool load(tGame &game, const string &name, tLastMoves &lastMoves); //Loads a board depending on the name

void save(const tGame &game, const string &name, tLastMoves lastMoves); //Saves a board with a given name

string fileToLoad(); //Ask the user for the file name to load

void askSaveGame(tGame game, tLastMoves lastMoves); //Ask the user for saving the game

//Display
void show(const tGame &game); //Displays the board on the screen

void displayMovements(tPossibles possibles); //Displays the possible moves of a peg

//Type Conversion
tMovements charToMovement(char character);

//Terminal color
void backgroundColor(int color);

//Input
bool askForPeg(tMove &moves, tGame game); //Ask the user for a peg

tMovements playerMovement(tPossibles possibles); //Ask the user for a direction

//Check valid moves
bool validMoves(tPossibles &possibles, int row, int column, tGame game); //Checks the possibles moves of a peg

bool possibleMove(tPossibles possibles, tMovements move); //Checks that the color input of the player is valid

void any_Peg_can_Move(tGame &game); //Checks that the game is not on deadlock

//Runs the game
void match(tGame &game, tLastMoves &lastMoves); //Runs the game

void executeMove(tGame &game, tMove moves); //Make a move choosen by the player

void gameState (tGame &game, tMove moves); //Checks the current state of the game

//Check Peg
bool checkPeg(tGame game, int row, int column); //checks that the selection of the player is a peg

//Random board generation
void initBoard(tMatrix matrix); //Inicializate board

void setGoal(tGame &game); //Set a random goal on the matrix

void generateBoard(tGame &game, int moves, tLastMoves lastMoves); //Creates a random board

bool inverseMove(tGame &game); //Select a random peg and move it

bool validInverseMoves(tPossibles &possibles, tGame game, int row, int column); //Checks valid inverse moves for a given peg

void executeInverseMove(tGame &game, int number, int row, int column); //Makes an inverse move

//Search Cell
void seachCell(tGame game, int &row, int &column, int randomCell); //Seach a random peg in the matrix

//Initialate array
void initPossibles(tPossibles possibles); //Initializate the bool array possibles

void initRepeatedRandom(tRepeatedRandom repeatedRandom); //Initialize the array of repeated randoms

//Count repeated randoms
int numRepeatedRandom(tRepeatedRandom repeatedRandom); //Counts the number of repeated randoms

//Undo Move
void initLastMove(tLastMoves &lastMoves); //Initializate the lastMove structure with -1 and movement WRONG

void saveLastMove(tLastMoves &lastMoves, tMove moves); //Stores the last move

void useLastMove(tLastMoves &lastMoves); //Shifts the array to the left (lose [0])

bool checkLastMove(tLastMoves lastMoves); //Checks if there is a last move avaliable

void executeInverseMove2(tGame &game, tLastMoves lastMoves); //Move a peg backwards

int askUndoMove(); // Asks the user if he wants to make a move or undo the last movement



/*

NOTES AND COMMENTS

1. I decided to save the last N movements on the file

2. I did not join the executeInverseMove and executeInverseMove2 because the first one is pointing the peg and the second one is pointing the original position of the peg.

3. In order to find the limit of the backwards movements of a board I tried to use a counter of random numbers. When a peg cannot move the random number of that peg (for example, the peg number 6, when I seach for it, in a matrix with 10 pegs) is stored in the array. If the array has the maximun number of possible randoms, then no peg can me moved backwards and the generation of the board is stopped. (I could use a function similar to any_Peg_Can_Move but I just wanted to try with this method).


INFORMATION OF THE FILE

1. Dimension

2. Initial Pegs

3. Row Goal

4. Column Goal

5. Matrix

6. Move Counter

7. Number of Last Movements Stored

7. Information of N lastMovements


FINISH

2. Join some functions.

3. Create a function any_Peg_Can_Move backwards.

*/