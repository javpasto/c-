//Javier Pastor Ramirez

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include <cctype>
#include <ctime>
#include <iomanip>

////////////////////
//Global Constants//
////////////////////
const int COLORS_EASY = 4; //Number of colors for easy mode
const int COLORS_HARD = 7; //Number of colors for hard mode
const int MAX_SEQUENCES = 10; //For the easy mode
const int MAX_SEQUENCES_HARD = 15; //For the hard mode
const int MAX_COLORS = 12; //Maximun number of colors in the sequence for the easy mode
const int MAX_COLORS_HARD = 20; //Maximun number of colors in the sequence for the hard mode
const int MAX_PLAYERS = 10; //Maximun number of players in the top
const int INITIAL_HINTS = 3; //Initial number of hints
const string FileName = "top.txt"; //For the file with the best 10 players

///////////////////
//Type Definition//
///////////////////
typedef enum tColors { Red, Green, Blue, Yellow, White, Pink, Orange };
typedef enum tMode { Exit, Easy, Hard, Hall_of_Fame, BestScore };
typedef tColors tSequence[MAX_COLORS_HARD]; //Filled only when the player chooses Hard mode
typedef string tTopPlayer[MAX_PLAYERS]; //For the top players name
typedef double tScore[MAX_PLAYERS]; //For the top players score

//////////////
//Prototypes//
//////////////
tMode menu(); //Displays the menu and returns the user input

//Type conversion
tColors intToColor(int number); //Converts int to tColor
tColors charToColor(char color); //Converts char to tColor
string tColorsToString(tColors number); //Converts tColor to string

//Color generators
void generateColor(tSequence colorSequence, tMode mode, int numColors); //Adds a color to the sequence
void generateSequence(tSequence colorSequenc, tMode mode, int numColors); //Generates a random sequence

//Display functions
void showSequece(const tSequence colorSequence, int number); //Displays the color sequence that the user has to input
void showTopTen(tTopPlayer topPlayer, tScore topScores, string name); //Displays the Hall of Fame
void showBestPlayer(tTopPlayer topPlayer, tScore topScores); //Show the best(s) player(s) in the Hall of Fame

//Test user input
bool testColor(const tSequence colorSequence, int index, tColors color); //Return true if the color is correct

//Use hints for the hard mode
bool useHint(const tSequence colorSeuqnece, int index, int &numHints); //Return true if the player can use a hint

//Runs the game
double gameStart(string name, tMode mode, int numHints);

//For the score
void loadTopTen(tTopPlayer topPlayer, tScore topScores); //Loads the information from the "top.txt" file
void saveTopTen(tTopPlayer topPlayer, tScore topScores); //Creates a file storing the score and names
int findNameTop(const tTopPlayer topPlayer, string name); //Checks if the player is already in the Hall of Fame
void sortTopSequences(tTopPlayer topPlayer, tScore topScores); //Bubble Sort
void addToTop(tTopPlayer topPlayer, tScore topScores, string name, int score, int place); //Adds the player to the Hall of Fame or update his score

//User color input
char userInput(tMode mode); //Checks that the color input is a color of the enumerated type tColors


int main() {
	tTopPlayer topPlayer;
	tScore topScores;
	string name;
	tMode mode = tMode(1); //Initilice to enter the menu
	int numHints = INITIAL_HINTS; //The maximun number of hints
	int score = 0;
	int place; //For the place in the top array

	srand(time(NULL)); //For the rand function

	loadTopTen(topPlayer, topScores); //Loads the top.txt file and sorts it

	cout << "Player name: ";
	getline(cin, name);

	while (mode != tMode(0)) {
		mode = menu();

		switch (mode)
		{
		case Easy:
			score = gameStart(name, mode, numHints);
			break;
		case Hard:
			score = gameStart(name, mode, numHints);
			break;
		case Hall_of_Fame:
			showTopTen(topPlayer, topScores, name);
			break;
		case BestScore:
			showBestPlayer(topPlayer, topScores);
			break;
		}
		
		if ((mode == Easy) || (mode == Hard)) {
			place = findNameTop(topPlayer, name);
			addToTop(topPlayer, topScores, name, score, place);
			saveTopTen(topPlayer, topScores);
			numHints = INITIAL_HINTS; //To reset the number of hints for the next game 
		}

		cin.sync(); //To avoid extra characters for the menu function
	}

	cout << "Press any key to end the program . . ." << endl;
	system("pause > null");
	return 0;
}


tMode menu() {
	int option = -1; //Initilice to enter the menu

	while ((option < 0) || (option > 4)) {
		cout << "1 - Play: Easy Mode" << endl
			<< "2 - Play: Hard Mode" << endl
			<< "3 - Hall of Fame" << endl
			<< "4 - Player(s) with the highest score" << endl
			<< "0 - Exit" << endl
			<< "Your option: ";
		cin >> option;

		if ((option < 0) || (option > 4))
			cout << "The option must be between 0 and 4." << endl << endl;
	}

	cout << endl << endl;

	return tMode(option);
}

//Type conversion
tColors intToColor(int number) {
	return tColors(number);
}

tColors charToColor(char color) {
	tColors colorReturn;

	if (color == 'R')
		colorReturn = intToColor(0); //colorReturn = Red;
	else if (color == 'G')
		colorReturn = intToColor(1);
	else if (color == 'B')
		colorReturn = intToColor(2);
	else if (color == 'Y')
		colorReturn = intToColor(3);
	else if (color == 'W') //Hard
		colorReturn = intToColor(4);
	else if (color == 'P') //Hard
		colorReturn = intToColor(5);
	else if (color == 'O') //Hard
		colorReturn = intToColor(6);

	return colorReturn;
}

string tColorsToString(tColors number) {
	string str;

	if (number == 0)
		str = "Red";
	else if (number == 1)
		str = "Green";
	else if (number == 2)
		str = "Blue";
	else if (number == 3)
		str = "Yellow";
	else if (number == 4)
		str = "White";
	else if (number == 5)
		str = "Pink";
	else if (number == 6)
		str = "Orange";

	return str;
}

//Color generators
void generateColor(tSequence colorSequence, tMode mode, int numColors) {

	if (mode == intToColor(1))
		colorSequence[numColors] = intToColor(rand() % COLORS_EASY);
	else
		colorSequence[numColors] = intToColor(rand() % COLORS_HARD);
} //Generates one more color when the sequences the players input is correct and it is not the last sequence

void generateSequence(tSequence colorSequence, tMode mode, int numColors) {

	for (int i = 0; i < numColors; i++) { //Only generates the first colors of the sequence: 3 for Easy, 5 for Hard
		if (mode == intToColor(1))
			colorSequence[i] = intToColor(rand() % COLORS_EASY);
		else
			colorSequence[i] = intToColor(rand() % COLORS_HARD);
	}
}

//Display functions
void showSequece(const tSequence colorSequence, int number) {

	for (int i = 0; i < number; i++) {

		cout << tColorsToString(colorSequence[i]);

		if (i + 1 < number)
			cout << " - ";

	}

	cout << endl;
}

void showTopTen(tTopPlayer topPlayer, tScore topScores, string name) {

	cout << setw(8) << left << "SCORE:" << "POS: " << "NAME:" << endl;

	if (topScores[0] > 0) {
		for (int i = 0; i < MAX_PLAYERS; i++) {
			if (topScores[i] > 0)
				cout << setw(7) << left << topScores[i] << " " << setw(2) << left << i + 1 << " - " << topPlayer[i];

			if (topPlayer[i] == name) //Shows the arrow in the position of the player
				cout << " <---";

			cout << endl;
		}
	}
	else
		cout << "Hall of Fame empty" << endl;

	cout << endl << endl;

} //I decided to add the string name as a parameter to show the player position in the top ten with an arrow

void showBestPlayer(tTopPlayer topPlayer, tScore topScores) {
	bool equal = false;
	int counter = 1;

	if (topScores[0] > 0) {
		cout << "Name: " << topPlayer[0] << endl
			<< "Score: " << topScores[0] << endl << endl;

		if (topScores[0] == topScores[counter])
			equal = true;

		while (equal) {
			cout << "Name: " << topPlayer[counter] << endl
				<< "Score: " << topScores[counter] << endl << endl;
			equal = false;
			if (topScores[counter] == topScores[counter + 1])
				equal = true;
			if (counter == MAX_PLAYERS)
				equal = false;
			counter++;
		}
	}
	else
		cout << "Hall of Fame empty" << endl;

	cout << endl << endl;
}

//Test user input
bool testColor(const tSequence colorSequence, int index, tColors color) {
	bool correct = true;

	if (colorSequence[index] != color) {
		correct = false;
	}

	return correct;
}

//Use hints for the hard mode
bool useHint(const tSequence colorSequence, int index, int &numHints) {
	bool correct = false;

	if (numHints > 0) { //If the player have hints remaining it displays the color
		numHints--;
		cout << "The next color is " << tColorsToString(colorSequence[index]) << ". You have " << numHints << " remaining hints!" << endl;
		correct = true;
	}

	return correct;
}

//Runs the game
double gameStart(string name, tMode mode, int numHints) {
	int rounds = 0, numColors = 3, index = 0, maxRounds = MAX_SEQUENCES;
	int score = 0; // For the score of the game
	bool correct = true, hints = false;
	tSequence colorSequence;
	char input;
	tColors colorInput;

	if (mode == tMode(2)) {
		numColors = 5; //Set the initial number of colors for the hard mode
		maxRounds = MAX_SEQUENCES_HARD; //Set the number of sequences for the hard mode
	}

	generateSequence(colorSequence, mode, numColors); //Generates a new sequence each time the game starts

	while ((rounds < maxRounds) && (correct)) {
		cout << endl << "Sequence Number " << rounds + 1 << ": ";

		showSequece(colorSequence, numColors);

		cout << "Press any key o continue . . ." << endl;
		system("pause > null");
		system("cls");

		cout << name << ", type the " << numColors << "-color sequence: " << endl;

		while ((index < numColors) && (correct)) {
			input = userInput(mode);

			if (input == 'X') { //If the player want to use a hint
				hints = useHint(colorSequence, index, numHints);

				if (!hints) {
					cout << "You have use all your hints, try to guess it by yourself!";

					while (input == 'X'){ //In order to avoid the X input if the player does not have remaining hints
						input = userInput(mode);
					}
					colorInput = charToColor(input);
					correct = testColor(colorSequence, index, colorInput);

					score += 5; // + 5 if it is a correct color

					if (!correct) {
						cout << "There was a mistake in the last Sequence!" << endl;
						score -= 5;
					}

				}
				else {
					score -= 7; //Substracts 7 if the user use a hint

					if (score < 0) //Only positive score
						score = 0;
				}
			}

			else {
				colorInput = charToColor(input);
				correct = testColor(colorSequence, index, colorInput);

				score += 5; // + 5 for each correct color

				if (!correct) {
					cout << "There was a mistake in the last Sequence!" << endl;
					score -= 5;
				}

			}

			input = 'a'; //To enter the loop again

			index++; //for the array index

		}

		index = 0; //Initialice to 0 to start from the first color of the array in each sequence
		rounds++;

		if (correct) {
			score += 10; // + 10 for each correct sequence
			cout << "Congratulations, you guessed sequence number " << rounds << "!";
		}

		if ((rounds < MAX_SEQUENCES_HARD) && (correct)) {
			generateColor(colorSequence, mode, numColors); //Adds a color to the array if the last sequence was correct and it is not the last sequence
			numColors++; //Add after because the array start at 0
		}

	}

	if (correct) {
		cout << "Congratulations, you won the game!!!";
	}
	else
		cout << "You reached sequence number " << rounds << ". Good luck the next time!";

	cout << endl << endl;

	if (mode == intToColor(2)) //Multiply the score by 1.5 if the player chooses the Hard mode
		score = score * 1.5;

	return score;
}

//For the score
void loadTopTen(tTopPlayer topPlayer, tScore topScores)	 {
	ifstream file;
	char auxiliar;

	file.open(FileName.c_str());
	if (file.is_open()) {
		for (int i = 0; i < MAX_PLAYERS; i++) {
			file >> topScores[i];
			file.get(auxiliar);
			getline(file, topPlayer[i]);
		}
		file.close();
	}
	else
		cout << "The top player file could not be opened." << endl << endl;

	sortTopSequences(topPlayer, topScores);
}

void saveTopTen(tTopPlayer topPlayer, tScore topScores) {
	ofstream file;

	file.open(FileName.c_str());
	if (file.is_open()) {
		for (int i = 0; i < MAX_PLAYERS; i++) {
			if (topScores[i] > 0)
				file << topScores[i] << " " << topPlayer[i] << endl; //Save the scores and then the names in order to use getline on the names
		}
		file.close();
	}
	else
		cout << "The top player file could not be created." << endl << endl;
}

int findNameTop(const tTopPlayer topPlayer, string name) {
	int place = -1; //Initilice to -1 in order to know if the string name is not in the array topPlayer[]

	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (topPlayer[i] == name)
			place = i;
	}

	return place; //Returns the place of the name
}

void sortTopSequences(tTopPlayer topPlayer, tScore topScores) { //Bubble Sort
	int auxiliarScore; //Auxiliar for the score
	string auxiliarStr; //Auxiliar for the name

	for (int i = 0; i < MAX_PLAYERS - 1; i++) { //This loop only makes the for inside execute 9 times
		for (int j = 0; j < MAX_PLAYERS - 1; j++) { //This loop executes 9 * 9 = 81 times
			if (topScores[j] < topScores[j + 1]) { //If the score on the right is lower than the score in the left the function exchanges them
				auxiliarScore = topScores[j]; //Exchanges the scores
				topScores[j] = topScores[j + 1];
				topScores[j + 1] = auxiliarScore;
				auxiliarStr = topPlayer[j]; //Exchanges the names
				topPlayer[j] = topPlayer[j + 1];
				topPlayer[j + 1] = auxiliarStr;
			}
		}
	}

}

void addToTop(tTopPlayer topPlayer, tScore topScores, string name, int score, int place){

	if (place == -1) { //If is a new player
		if (score > topScores[9]) { //Only adds it if it has a higher score than the last player of the top ten
			topScores[9] = score;
			topPlayer[9] = name;
			cout << "Your are now in the Hall of Fame!!!" << endl << endl;

			sortTopSequences(topPlayer, topScores);
			showTopTen(topPlayer, topScores, name); //Shows the position in the Hall of Fame of the new player
		}
	}
	else  //If its the same name
		if (topScores[place] < score) {
			topScores[place] = score;
			topPlayer[place] = name;
			cout << "Your score has been updated." << endl << endl;

			sortTopSequences(topPlayer, topScores);
			showTopTen(topPlayer, topScores, name); //Shows the new position in the Hall of Fame
		}

	cout << endl << endl;
}

//User color input
char userInput(tMode mode) {
	char character = 'a'; //Initilice in order to enter the while

	if (mode == intToColor(1)) //For easy mode
		while ((character != 'R') && (character != 'G') && (character != 'B') && (character != 'Y') && (character != 'X')) {
			cin >> character;
			character = toupper(character);
		}
	else //For hard mode
		while ((character != 'R') && (character != 'G') && (character != 'B') && (character != 'Y') && (character != 'W') && (character != 'P') && (character != 'O') && (character != 'X')) {
			cin >> character;
			character = toupper(character);
		}

	return character;
}

/*
//The structure for the score if you do not want to use arrays

typedef struct //This contains the players name and the score
{
string player;
double score;

} tTopTen;

typedef tTopTen tSequenceTop[MAX_PLAYERS]; //The array with 2 dimensions and 10 slots

typedef struct //The structure declared to have the array linked with a counter
{
tSequenceTop sequence;
int counter;

} tArrayTop;
*/