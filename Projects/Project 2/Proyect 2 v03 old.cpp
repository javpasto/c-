//Javier Pastor Ramirez

#include <iostream>
using namespace std;
#include <cmath>
#include <string>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iomanip>

//Global Constant
const int COLORS_NUM = 4;
const int MAX_COLORS_HARD = 20;
const int MAX_SEQUENCES = 10;
const int MAX_SEQUENCES_HARD = 15;
const int MAX_COLORS = 12;
const int MAX_PLAYERS = 10;

//Type Definition
typedef enum tColors { Red, Green, Blue, Yellow , White, Pink, Orange};
typedef enum tMode { Exit, Easy, Hard, Hall_of_Fame, BestScore };
typedef tColors tSequence[MAX_COLORS];
typedef string tTopPlayer[MAX_PLAYERS]; //For the players name
typedef double tScore[MAX_PLAYERS]; //For the score number

//Prototype
tMode menu();
tColors charToColor(char color);
tColors intToColor(int number);
string tColorsToString(tColors number);
void generateSequence(tSequence colorSequenc, tMode mode, int numColors);
void generateColor(tSequence colorSequence, int numColors);
bool testColor(const tSequence colorSequence, int index, tColors color);
void showSequece(const tSequence colorSequence, int number);
bool useHint(const tSequence colorSeuqnece, int index, int &numHints);
double gameStart(string name, tMode mode, int numHints);
void loadTopTen(tTopPlayer topPlayer, tScore topScores);
void saveTopTen(tTopPlayer topPlayer, tScore topScores);
void showTopTen(tTopPlayer topPlayer, tScore topScores);
void sortTopSequences(tTopPlayer topPlayer, tScore topScores); //Bubble Sort
void showBestPlayer(tTopPlayer topPlayer, tScore topScores);
void addToTop(tTopPlayer topPlayer, tScore topScores, string name, int score);


int main(){
	tTopPlayer topPlayer;
	tScore topScores;
	string name;
	tMode mode = tMode(1);
	int numHints = 3;
	int score = 0;

	loadTopTen(topPlayer, topScores);
	sortTopSequences(topPlayer, topScores);

	cout << "Player name: ";
	cin >> name;

	while (mode != tMode(0)){
		mode = menu();

		srand(time(NULL));

		switch (mode)
		{
		case Easy:
			score = gameStart(name, mode, numHints);
			break;
		case Hard:
			score = gameStart(name, mode, numHints);
			break;
		case Hall_of_Fame:
			showTopTen(topPlayer, topScores);
			break;
		case BestScore:
			showBestPlayer(topPlayer, topScores);
			break;
		}

		addToTop(topPlayer, topScores, name, score);
		saveTopTen(topPlayer, topScores);

		cin.sync();
	}

	sortTopSequences(topPlayer, topScores);
	saveTopTen(topPlayer, topScores);

	system("pause");
	return 0;
}


tMode menu(){
	int option = -1;

	while ((option < 0) || (option > 4)){
		cout << "1 - Play: Easy Mode" << endl
			<< "2 - Play: Hard Mode" << endl
			<< "3 - Hall of Fame" << endl
			<< "4 - Player(s) with the highest score" << endl
			<< "0 - Exit" << endl
			<< "Your option: ";
		cin >> option;
	}

	return tMode(option);
}

tColors charToColor(char color){
	tColors colorReturn;

	if (color == 'R')
		colorReturn = intToColor(0);
	else if (color == 'G')
		colorReturn = intToColor(1);
	else if (color == 'B')
		colorReturn = intToColor(2);
	else if (color == 'Y')
		colorReturn = intToColor(3);
	else if (color == 'W')
		colorReturn = intToColor(4);
	else if (color == 'P')
		colorReturn = intToColor(5);
	else if (color == 'O')
		colorReturn = intToColor(6);

	return colorReturn;
}

tColors intToColor(int number){
	return tColors(number);
}

string tColorsToString(tColors number){
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

void generateSequence(tSequence colorSequence, tMode mode, int numColors){
	for (int i = 0; i < numColors; i++){
		colorSequence[i] = intToColor(rand() % COLORS_NUM);
	}
}

void generateColor(tSequence colorSequence, int numColors){
	colorSequence[numColors] = intToColor(rand() % COLORS_NUM);
}

bool testColor(const tSequence colorSequence, int index, tColors color){
	bool correct = true;

	if (colorSequence[index] != color){
		correct = false;
	}

	return correct;
}

void showSequece(const tSequence colorSequence, int number){
	for (int i = 0; i < number; i++){
		cout << tColorsToString(colorSequence[i]) << " ";
	}
}

bool useHint(const tSequence colorSequence, int index, int &numHints){
	bool correct = false;

	if (numHints > 0){
		numHints--;
		cout << tColorsToString(colorSequence[index]) << endl << "There are " << numHints << " remaining hits." << endl;
		correct = true;
	}

	return correct;
}

double gameStart(string name, tMode mode, int numHints){
	int rounds = 0, numColors = 3, numColorsHard = 5, index = 0;
	int score = 0; // For the score of the game
	bool correct = true, hints = false;
	tSequence colorSequence;
	char input = 'a'; //To enter the while
	tColors colorInput;

	if (mode == tMode(2)){
		generateSequence(colorSequence, mode, numColorsHard);
		while ((rounds < MAX_SEQUENCES_HARD) && (correct)){
			cout << name << ", Sequence Number " << rounds + 1 << ": ";
			showSequece(colorSequence, numColorsHard);
			cout << endl;
			system("pause");
			system("cls");
			cout << name << ", enter the sequence: ";
			while ((index < numColorsHard) && (correct)){
				while ((input != 'R') && (input != 'G') && (input != 'B') && (input != 'Y') && (input != 'W') && (input != 'P') && (input != 'O') && (input != 'X')){
					cin >> input;
					input = toupper(input);
				}
				if (input == 'X'){
					hints = useHint(colorSequence, index, numHints);
					if (!hints){
						cout << "You have use all your hints, try to guess it by yourself!";
						while ((input != 'R') && (input != 'G') && (input != 'B') && (input != 'Y') && (input != 'W') && (input != 'P') && (input != 'O') && (input != 'X')){
							cin >> input;
							input = toupper(input);
						}
						colorInput = charToColor(input);
						correct = testColor(colorSequence, index, colorInput);
						score += 5;
						if (!correct){
							cout << "There was a mistake in the last Sequence!" << endl;
							score -= 5;
						}
					}
					else{
						score -= 7;
						if (score < 0)
							score = 0;
					}
				}
				else{
					colorInput = charToColor(input);
					correct = testColor(colorSequence, index, colorInput);
					score += 5;
					if (!correct){
						cout << "There was a mistake in the last Sequence!" << endl;
						score -= 5;
					}
				}
				input = 'a';
				index++;
			}
			index = 0;
			if (correct)
				score += 10;
			if ((rounds < MAX_SEQUENCES_HARD - 1) && (correct)){
				generateColor(colorSequence, numColorsHard);
				numColorsHard++; //Add after because the array start at 0
			}
			rounds++;
		}
		score = score * 1.5;
	}
	else{
		generateSequence(colorSequence, mode, numColors);
		while ((rounds < MAX_SEQUENCES) && (correct)){
			cout << name << ", Sequence Number " << rounds + 1 << ": ";
			showSequece(colorSequence, numColors);
			cout << endl;
			system("pause");
			system("cls");
			cout << name << ", enter the sequence: ";
			while ((index < numColors) && (correct)){
				while ((input != 'R') && (input != 'G') && (input != 'B') && (input != 'Y')){
					cin >> input;
					input = toupper(input);
				}
				colorInput = charToColor(input);
				correct = testColor(colorSequence, index, colorInput);
				index++;
				score += 5;
				if (!correct){
					cout << "There was a mistake in the last Sequence!" << endl;
					score -= 5;
				}
				input = 'a';
			}
			if (correct)
				score += 10;
			index = 0;
			rounds++;
			if ((rounds < MAX_SEQUENCES) && (correct)){
				generateColor(colorSequence, numColors);
				numColors++; //Add after because the array start at 0
			}
		}
	}

	if (correct){
		cout << "Such clever, so player!!!";
	}
	else
		cout << "Such hard, so try..." << endl << "You finished at sequence number " << rounds;
	cout << endl << endl;

	if (score < 0) //To be sure that the score is not negative
		score = 0;

	return score;
}

void loadTopTen(tTopPlayer topPlayer, tScore topScores){
	ifstream file;

	file.open("top.txt");
	if (file.is_open()){
		for (int i = 0; i < MAX_PLAYERS; i++){
			file >> topScores[i] >> topPlayer[i];
		}
		file.close();
	}
	else
		cout << "The top player file could not be opened." << endl << endl;
}

void saveTopTen(tTopPlayer topPlayer, tScore topScores){
	ofstream file;

	file.open("top.txt");
	if (file.is_open()){
		for (int i = 0; i < MAX_PLAYERS; i++){
			if (topScores[i] > 0)
			file << topScores[i] << " " << topPlayer[i] << endl;
		}
		file.close();
	}
	else
		cout << "The top player file could not be created." << endl << endl;
}

void showTopTen(tTopPlayer topPlayer, tScore topScores){

	cout << setw(10) << left << "NAME:" << setw(5) << left << "SCORE:" << endl;

	if (topScores[0] > 0){
		for (int i = 0; i < MAX_PLAYERS; i++){
			if (topScores[i] > 0)
				cout << setw(10) << left << topPlayer[i] << setw(5) << left << topScores[i] << endl;
		}
	}
	else
		cout << "Hall of Fame empty";

	cout << endl << endl;

}

void sortTopSequences(tTopPlayer topPlayer, tScore topScores){ //Bubble Sort
	int auxiliarScore;
	string auxiliarStr;

	for (int i = 0; i < MAX_PLAYERS - 1; i++){
		for (int j = 0; j < MAX_PLAYERS; j++){
			if (topScores[j] < topScores[j + 1]){
				auxiliarScore = topScores[j];
				topScores[j] = topScores[j + 1];
				topScores[j + 1] = auxiliarScore;
				auxiliarStr = topPlayer[j];
				topPlayer[j] = topPlayer[j + 1];
				topPlayer[j + 1] = auxiliarStr;
			}
		}
	}

}

void showBestPlayer(tTopPlayer topPlayer, tScore topScores){
	bool equal = false;
	int counter = 1;

	if (topScores[0] > 0){
		cout << "Name: " << topPlayer[0] << endl
			<< "Score: " << topScores[0] << endl << endl;

		if (topScores[0] == topScores[counter])
			equal = true;

		while (equal){
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
}

void addToTop(tTopPlayer topPlayer, tScore topScores, string name, int score){
	if (score > topScores[9]){
		topScores[9] = score;
		topPlayer[9] = name;
		cout << "You are now in the Hall of Fame!!!" << endl << endl;
	}
}

//Cambiar la entrada al Hall of Fame comprobando que el nombre sea el mismo y sustituyendo en valor en vez de hacerlo con el ultimo
//Revisar menu();
//Optimizar gameStart
//Revisar funciones pequeñas con el cambio de la version 2
//Revisar con los detalles de implementacion