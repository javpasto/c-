//Grupo U Javier Pastor

#include <iostream>
using namespace std;

bool check();

int main() {
	int casosDePrueba;

	cin >> casosDePrueba;

	for (int i = 0; i < casosDePrueba; i++) {
		if (check()) { cout << "SI"; }
		else { cout << "NO"; }
		cout << endl;
	}

	return 0;
}

bool check() {
	bool correct = false;
	int n, p, maxU = 0, auxiliar;

	cin >> n >> p;

	for (int i = 0; i < p + 1; i++) {
		cin >> auxiliar;
		if (i == 0) { maxU = auxiliar; }
		else { if (maxU < auxiliar) { maxU = auxiliar; } }
	}

	int minW = maxU + 1;

	for (int i = p + 2; i < n + 1; i++) {
		cin >> auxiliar;
		if (i == p + 2) { minW = auxiliar; }
		else { if (minW > auxiliar) { minW = auxiliar; } }
	}

	if (maxU < minW) { correct = true; }


	return correct;
}