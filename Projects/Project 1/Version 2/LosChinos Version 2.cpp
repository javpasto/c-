#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

//Global types
const int NOONE = 0, MACHINE = 1, HUMAN = 2;

//Prototypes
int machineCoins(int coinamount);
int humanCoins(int coinAmount);
int machineBet(int coinAmount, int coinAmountM);
int humanBet(int betM, int coinAmountH, int cointAmount);
int whoWins(int coinAmountM, int coinAmountH, int betM, int betH);
int menu();
bool showRules();
int askForScore();
int askForCoins();
void game(int score, int coinAmount);

int main() {
	int option = 1, score = 2, coinAmount = 3;
	bool fileopen = true;

	while (option != 0) {

		//Menu
		option = menu();

		if (option == 1)
			score = askForScore();

		if (option == 2)
			coinAmount = askForCoins();

		if (option == 3)
			fileopen = showRules();

		if (fileopen == false)
			cout << "The is something wrong with the file!" << endl;

		if (option == 4)
			game(score, coinAmount);
		}

		return 0;
	}

int machineCoins(int coinAmount) {
		int coinM;

		coinM = rand() % (coinAmount + 1);

		return coinM;
	}

int humanCoins(int coinAmount) {
		int coinAmountH;

		cout << "Your number of coins (0-" << coinAmount << "): ";
		cin >> coinAmountH;

		while ((coinAmountH < 0) || (coinAmountH > coinAmount)) {
			cout << "Invalid number! Try again!" << endl << "Your number of coins (0 - " << coinAmount << "): ";
			cin >> coinAmountH;
		}

		return coinAmountH;
	}

int machineBet(int coinAmount, int coinAmountM) {
		int betM = 0;

		while (betM < 1)
			betM = coinAmountM + (rand() % (coinAmount + 1));

		return betM;
	}

int humanBet(int betM, int coinAmountH, int coinAmount) {
		int betH;

		cout << "Your bet (0-" << coinAmount *2 << "): ";
		cin >> betH;

		while ((betH > coinAmountH + 3) || (betH < coinAmountH) || (betH == betM)) {
			cout << "Dont lie! Try again!" << endl;
			cout << "Your bet (0-" << coinAmount * 2 << "6): ";
			cin >> betH;

		}

		return betH;
	}

int whoWins(int coinAmountM, int coinAmountH, int betM, int betH) {
		int winner;
		int totalcoins = coinAmountH + coinAmountM;

		if (totalcoins == betM)
			winner = MACHINE;
		if (totalcoins == betH)
			winner = HUMAN;
		if ((totalcoins != betM) && (totalcoins != betH))
			winner = NOONE;

		return winner;
	}

int menu(){
		int option = -1;
		while ((option < 0) || (option > 4)){
			cout << "1 - Change maximun score (2 by default)" << endl
				<< "2 - Change maximun number of coins (3 by default)" << endl
				<< "3 - about 'LosChinos'" << endl
				<< "4 - Play" << endl
				<< "0 - Exit" << endl
				<< "Option: ";
			cin >> option;
			cout << endl;
		}
		return option;
	}

bool showRules(){
	ifstream rules;
	string str = "";
	bool fileopen = true;

	rules.open("rules.txt");
	if (rules.is_open()){
		getline(rules, str);
		while (str != "XXX"){
			cout << str << " ";
			getline(rules, str);
		}
		cout << endl << endl;
	}
	else
		fileopen == false;

	rules.close();

	return fileopen;
}

int askForScore(){
		int score = -1;
		while (score <= 0){
			cout << "Maximun score:";
			cin >> score;
		}
		cout << endl;
		return score;
	}

int askForCoins(){
		int coinamount = -1;
		while (coinamount <= 0){
			cout << "Maximun number of coins:";
			cin >> coinamount;
		}
		cout << endl;
		return coinamount;
	}

void game(int score, int coinAmount){

		int humanWon = 0, machineWon = 0, wonround; //For the rounds won
		int coinAmountH = 0, coinAmountM = 0, betM, betH;

		while ((humanWon != score) && (machineWon != score)){
			coinAmountM = machineCoins(coinAmount);
			coinAmountH = humanCoins(coinAmount);
			betM = machineBet(coinAmount, coinAmountM);

			cout << "I think we have " << betM << " coins together." << endl
				<< "Your turn..." << endl;

			betH = humanBet(betM, coinAmountH, coinAmount);

			cout << "Machine: " << coinAmountM << endl
				<< "Player: " << coinAmountH << endl;

			wonround = whoWins(coinAmountM, coinAmountH, betM, betH);

			if (wonround == MACHINE) {
				machineWon++;
				cout << "Machine wins!";
			}
			if (wonround == HUMAN) {
				humanWon++;
				cout << "You win!" << endl;
			}
			if ((wonround != HUMAN) && (wonround != MACHINE))
				cout << "No one wins." << endl;
			cout << endl;
		}

		if (humanWon == score) {
			cout << "You won the game!!!" << endl
				<< "Machine won " << machineWon << " round(s)";

		}
		if (machineWon == score) {
			cout << "The machine won the game!!!" << endl
				<< "You won " << humanWon << " round(s)";

		}
		cout << endl << endl;
	}