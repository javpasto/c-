#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
using namespace std;

//Global constants
const int NOONE = 0, MACHINE = 1, HUMAN = 2; //Constant for the won round.

//Prototypes.
int machineCoins(int COINAMOUNT);
int humanCoins();
int machineBet(int COINAMOUNT, int coinAmountM);
int humanBet(int betM, int coinAmountH);
int whoWins(int coinAmountM, int coinAmountH, int betM, int betH);

int main() {
	const int SCORE = 2, COINAMOUNT = 3;
	int humanWon = 0, machineWon = 0, wonround; //Count the rounds won.
	int coinAmountH = 0, coinAmountM = 0;
	int betM, betH;

	srand(time(NULL)); //For random numbers.

	while ((humanWon != SCORE) && (machineWon != SCORE)) {
		coinAmountM = machineCoins(COINAMOUNT); //Generates a random number of coins for the machine.
		coinAmountH = humanCoins(); //Player choose coins.
		betM = machineBet(COINAMOUNT, coinAmountM); //Machine makes a bet.

		cout << "I think we have " << betM << " coins together." << endl
			<< "Your turn..." << endl;

		betH = humanBet(betM, coinAmountH); //Player makes a bet.

		cout << "Machine: " << coinAmountM << endl
			<< "Player: " << coinAmountH << endl;

		wonround = whoWins(coinAmountM, coinAmountH, betM, betH); //Decide who wins the round.

		if (wonround == MACHINE) { //Add 1 round won to machine, if machine won the round.
			machineWon++;
			cout << "Machine wins!" << endl;
		}
		else if (wonround == HUMAN) { //Add 1 round won to the player, if the player won the round.
			humanWon++;
			cout << "You win!" << endl;
		}
		else
			cout << "No one wins." << endl;
	}

	if (humanWon == SCORE) { //Displayed if Player wins the game.
		cout << "You won the game!!!" << endl
			<< "Machine won " << machineWon << "round(s)";

	}
	if (machineWon == SCORE) { //Displayed if Machine wins the game.
		cout << "The machine won the game!!!" << endl
			<< "You won " << humanWon << "round(s)";

	}

	return 0;
}

int machineCoins(int COINAMOUNT) {
	int coinM;

	coinM = rand() % (COINAMOUNT + 1); //Generates a Random number between 0 and 3 for the machine coins

	return coinM;
}

int humanCoins() {
	int coinAmountH;

	cout << "Your number of coins (0-3): ";
	cin >> coinAmountH;

	while ((coinAmountH < 0) || (coinAmountH > 3)) {
		cout << "Invalid number! Try again!" << endl << "Your number of coins (0 - 3): ";
		cin >> coinAmountH;
	}

	return coinAmountH;
}

int machineBet(int COINAMOUNT, int coinAmountM) {
	int betM = 0;

	betM = coinAmountM + (rand() % (COINAMOUNT + 1)); //Adds the number of coins of the machine in order to be always equal or greater than the machine´s coins.

	return betM;
}

int humanBet(int betM, int coinAmountH) {
	int betH;

	cout << "Your bet (0-6): ";
	cin >> betH;

	while ((betH > coinAmountH + 3) || (betH < coinAmountH) || (betH == betM)) { //Can not be equal to the machine´s bet and has to be more than the player coins.
		cout << "Dont lie! Try again!" << endl;
		cout << "Your bet (0-6): ";
		cin >> betH;
	}

	return betH;
}

int whoWins(int coinAmountM, int coinAmountH, int betM, int betH) { //I use more arguments to use the constant inside the function.
	int winner;
	int totalcoins = coinAmountH + coinAmountM; //Adds the total number of coins.

	if (totalcoins == betM)
		winner = MACHINE;
	else if (totalcoins == betH)
		winner = HUMAN;
	else
		winner = NOONE;

	return winner; //Returns NOONE, MACHINE or HUMAN.
}