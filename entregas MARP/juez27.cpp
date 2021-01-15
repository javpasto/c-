#include <iostream>
#include <string>
#include <climits>

using namespace std;


bool resuelveCaso() {

	int numAgujeros, longParches;
	cin >> numAgujeros >> longParches;

	if (!cin) return false;

	int count = 0; //Cuenta el numero de parches
	int cubierto = 0; //Cuenta hasta q distancia esta cubierta la manguera

	int in; //Input
	for (int i = 0; i < numAgujeros; i++) {
		cin >> in;
		if (in > cubierto) {
			count++;
			cubierto = in + longParches;
		}
	}

	cout << count << "\n";

	return true;
}

int main() {

	while (resuelveCaso()) {}
	return 0;
}