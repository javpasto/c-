//File senku.h

#include <string>
#include <fstream>
#include <windows.h>
using namespace std;
#include <iomanip>

////////////////////
//Global Constants//
////////////////////
const int DIM = 6; //For the dimensions of the matrix
const string name = "board.txt";

//////////////////////
//Arrays and Structs//
//////////////////////

typedef enum tCell { UNAV = 0, EMPTY = 2, PEG = 10 }; //For the type of the cell
typedef enum tState { DEADLOCK, WON, PLAYING, ABANDONED }; //For the status of the game

typedef tCell tMatrix[DIM][DIM];

typedef struct {

	tMatrix matrix;
	int rowGoal;
	int columnGoal;
	int initialPegs;
	int movements;
	tState state;

} tGame;

//////////////
//Prototypes//
//////////////

//File
bool load(tGame &game, const string &name);
void save(const tGame &game, const string &name);

//Display
void show(const tGame &game);

//Terminal color
void backgroundColor(int color);