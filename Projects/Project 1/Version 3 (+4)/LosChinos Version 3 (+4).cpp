#include <iostream>
using namespace std;
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

//Global types
const int NOONE = 0, MACHINE = 1, HUMAN = 2;

//Prototypes
int machineCoins(int coinamount);
int humanCoins(int coinAmount);
int machineBet(int coinAmount, int coinAmountM);
int humanBet(int betM, int coinAmountH, int cointAmount);
int player1Bet(int betM, int coinAmountP, int coinAmount);
int whoWins(int coinAmountM, int coinAmountH, int betM, int betH);
int menu();
bool showRules();
int askForScore();
int askForCoins();
void game(int score, int coinAmount);
void autoGame(int score, int coinAmount);

int main() {
	int option = 1, score = 2, coinAmount = 3;
	bool fileopen = true;
	char auxiliar;
	ifstream config;
	ofstream newConfig;

	config.open("configP1.txt");
	if (config.is_open()){
		config >> score;
		config.get(auxiliar);
		config >> coinAmount;
		cout << "Values from the last game:";
	}
	else
		cout << "Default values:";
	cout << endl << "Score = " << score << endl << "Coins = " << coinAmount << endl << endl;

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

		if (option == 5)
			autoGame(score, coinAmount);
	
	}
	config.close();

	newConfig.open("configP1.txt");
	if (newConfig.is_open())
		newConfig << score << endl << coinAmount;
	else
		cout << endl << "The file could not be created.";
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

	while ((betH > coinAmountH + coinAmount) || (betH < coinAmountH) || (betH == betM)) {
		cout << "Dont lie! Try again!" << endl;
		cout << "Your bet (0-" << coinAmount * 2 << "): ";
		cin >> betH;

	}

	return betH;
}

int player1Bet(int betM, int coinAmountP, int coinAmount){
	int betP;

	betP = coinAmountP + (rand() % (coinAmount + 1));

	while (betP == betM) {
		betP = coinAmountP + (rand() % (coinAmount + 1));
	}

	return betP;
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
		while ((option < 0) || (option > 5)){
			cout << "1 - Change maximun score" << endl
				<< "2 - Change maximun number of coins" << endl
				<< "3 - about 'LosChinos'" << endl
				<< "4 - Play" << endl
				<< "5 - Play an automatic match" << endl
				<< "0 - Exit" << endl
				<< "Option: ";
			cin >> option;
			cout << endl;
			if (((option < 0) || (option > 5)))
				cout << "The option must be between 0 and 5" << endl << endl;
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
			cout << str << endl;
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
			cout << "Maximun score: ";
			cin >> score;
		}
		cout << endl;
		return score;
	}

int askForCoins(){
		int coinamount = -1;
		while (coinamount <= 0){
			cout << "Maximun number of coins: ";
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

void autoGame(int score, int coinAmount){

		int player1Won = 0, machineWon = 0, wonround; //For the rounds won
		int coinAmountP = 0, coinAmountM = 0, betM, betP;
		int countRounds = 0, matchContinue = 2; //For the automatic match
		int i = 1; //For the rounds count in Continue?
		const int MAXROUND = score * 100;
		int counter = 0;

		while ((player1Won != score) && (machineWon != score) && (countRounds != MAXROUND)){
			coinAmountM = machineCoins(coinAmount);
			coinAmountP = machineCoins(coinAmount);
			betM = machineBet(coinAmount, coinAmountM);

			cout << "I think we have " << betM << " coins together." << endl
				<< "Player 1 turn..." << endl;

			betP = player1Bet(betM, coinAmountP, coinAmount);

			cout << "Player 2: " << coinAmountM << endl
				<< "Player 1: " << coinAmountP << endl;

			wonround = whoWins(coinAmountM, coinAmountP, betM, betP);

			if (wonround == MACHINE) {
				machineWon++;
				cout << "Player 2 wins!";
			}
			if (wonround == HUMAN) {
				player1Won++;
				cout << "Player 1 wins!";
			}
			if ((wonround != HUMAN) && (wonround != MACHINE))
				cout << "No one wins.";
			cout << endl << endl;
			countRounds++; //For the automatic match
			counter++; //Rounds Played (Delete it)
			if (countRounds == MAXROUND){ //Continue?
				while ((matchContinue < 0) || (matchContinue > 1)){
					cout << "Do you want to continue the match?" 
						<< endl << "(Rounds played: " << countRounds * i << ")" << endl << "(Rounds won by Player 1: "
						<< player1Won << ")   " << "(Rounds won by Player 2: " << machineWon << ")" << endl
						<< "Type 1 to continue and 0 to stop: ";
					cin >> matchContinue;
					if ((matchContinue < 0) || (matchContinue > 1)){
						cout << endl << "Make sure to write 0 or 1" << endl << endl;
					}
				}
				if (matchContinue == 1)
					countRounds = 0;
				matchContinue = 2;
				i++;
			}
		}

		if (player1Won == score) {
			cout << "Player 1 won the game!!!" << endl
				<< "Player 2 won " << machineWon << " round(s)";

		}
		if (machineWon == score) {
			cout << "Player 2 won the game!!!" << endl
				<< "Player 1 won " << player1Won << " round(s)";

		}
		cout << endl << "Total rounds: " << counter << endl;
		cout << endl << endl;
	}