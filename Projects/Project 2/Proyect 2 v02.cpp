#include <iostream>
using namespace std;
#include <cmath>
#include <string>
#include <cctype>
#include <ctime>

//Global Constant
const int COLORS_NUM = 4;
const int MAX_COLORS_HARD = 7;
const int MAX_SEQUENCES = 10;
const int MAX_SEQUENCES_HARD = 15;
const int MAX_COLORS = 12;

//Type Definition
typedef enum tColors { Red, Green, Blue, Yellow , White, Pink, Orange};
typedef enum tMode { Exit, Easy, Hard };
typedef tColors tSequence[MAX_COLORS];

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
void gameStart(string name, tMode mode, int numHints);


int main(){
	string name;
	tMode mode = tMode(1);
	int numHints = 3;

	cout << "Player name: ";
	cin >> name;

	while (mode != tMode(0)){
		mode = menu();

		srand(time(NULL));

		if ((mode == tMode(1)) || (mode == tMode(2)))
			gameStart(name, mode, numHints);

		cin.sync();
	}

	system("pause");
	return 0;
}


tMode menu(){
	int option = -1;

	while ((option < 0) || (option > 2)){
		cout << "1 - Play: Easy Mode" << endl
			<< "2 - Play: Hard Mode" << endl
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

void gameStart(string name, tMode mode, int numHints){
	int rounds = 0, numColors = 3, numColorsHard = 5, index = 0;
	bool correct = true, hints = false;
	tSequence colorSequence;
	char input;
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
				cin >> input;
				input = toupper(input);
				if (input == 'X'){
					hints = useHint(colorSequence, index, numHints);
					if (!hints){
						cout << "You have use all your hints, try to guess it by yourself!";
						cin >> input;
						input = toupper(input);
						colorInput = charToColor(input);
						correct = testColor(colorSequence, index, colorInput);
						if (!correct)
							cout << "There was a mistake in the last Sequence!" << endl;
					}
				}
				else{
					colorInput = charToColor(input);
					correct = testColor(colorSequence, index, colorInput);
					if (!correct)
						cout << "There was a mistake in the last Sequence!" << endl;
				}
				index++;
			}
			index = 0;
			if ((rounds < MAX_SEQUENCES_HARD - 1) && (correct)){
				generateColor(colorSequence, numColorsHard);
				numColorsHard++; //Add after because the array start at 0
			}
			rounds++;
		}
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
				cin >> input;
				input = toupper(input);
				colorInput = charToColor(input);
				correct = testColor(colorSequence, index, colorInput);
				index++;
				if (!correct)
					cout << "There was a mistake in the last Sequence!" << endl;
			}
			index = 0;
			rounds++;
			if ((rounds < MAX_SEQUENCES) && (correct)){
				generateColor(colorSequence, numColors);
				numColors++; //Add after because the array start at 0
			}
		}
	}

	if (correct)
		cout << "Such clever, so player!!!";
	else
		cout << "Such hard, so try..." << endl << "You finished at sequence number " << rounds;
	cout << endl << endl;
}