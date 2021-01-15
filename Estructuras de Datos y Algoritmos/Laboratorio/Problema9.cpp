//Javier Pastor Ramirez

#include <iostream>
#include <string>
using namespace std;

int encontrarPatron(string original, string patron);

int main() {
	string original, patron;

	getline(cin, original);

	getline(cin, patron);

	cout << encontrarPatron(original, patron);

	return 0;
}

int encontrarPatron(string original, string patron) {
	int counter = 0;


	for (int i = 0; i < original.length(); i++) {
		bool ciclo = false;

		if (original[i] == patron[0]) { ciclo = true; }

		int auxiliar = 0;
		while (ciclo) {
			if (auxiliar = patron.length()) {
				counter++;
				ciclo = false;
				i += auxiliar - 1;
			}
			if (original[i + auxiliar] != patron[auxiliar]) {
				ciclo = false;
				i += auxiliar - 1;
			}
			auxiliar++;
		}

	}


	return counter;
}