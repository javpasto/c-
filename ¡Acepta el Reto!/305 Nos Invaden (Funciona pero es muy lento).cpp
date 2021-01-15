#include <iostream>
using namespace std;
#include <cmath>
#include <cctype>

//Global Constants
const int MAXCITY = 100000;

//Global Types
typedef int tCities[MAXCITY];

int main() {
	tCities invasors, invaded;
	int cities, auxiliar;
	long long int sumInvaded = 0;
	int counter = 0;

	for (int i = 0; i < MAXCITY; i++) {
		invaded[i] = 0;
		invasors[i] = 0;
	}

	cin >> cities;

	while (cities != 0) {

		for (int i = 0; i < cities; i++) //To read the input of Invasors
			cin >> invasors[i];

		for (int i = 0; i < cities; i++) //To read the input of Invaded
			cin >> invaded[i];

		for (int j = 0; j < MAXCITY; j++) {
			for (int i = 0; i < MAXCITY; i++) {
				if ((invasors[i] > invasors[i + 1]) && (invasors[i] != 0) && (invasors[i + 1] != 0)) {
					auxiliar = invasors[i];
					invasors[i] = invasors[i + 1];
					invasors[i + 1] = auxiliar;
				}
				if ((invaded[i] > invaded[i + 1]) && (invaded[i] != 0) && (invaded[i + 1] != 0)) {
					auxiliar = invaded[i];
					invaded[i] = invaded[i + 1];
					invaded[i + 1] = auxiliar;
				}
			}
		}

		for (int i = 0; i < MAXCITY; i++) {
			if (invaded[i] >= invasors[counter])
				counter++;

		}

		for (int i = 0; i < MAXCITY; i++) {
			invaded[i] = 0;
			invasors[i] = 0;
		}

		cout << counter << endl;
		counter = 0;
		sumInvaded = 0;

		cin >> cities;
	}

	return 0;
}