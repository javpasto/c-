#include <iostream>
#include <string>
#include <climits>

#include "PriorityQueue.h"
using namespace std;

struct registro {
	string nombre;
	int gravedad;
	int espera;
};

bool operator>(registro const&a, registro const&b) {
	return a.gravedad > b.gravedad || (a.gravedad == b.gravedad && a.espera > b.espera);
}

bool operator<(registro const&a, registro const&b) {
	return a.gravedad > b.gravedad || (a.gravedad == b.gravedad && a.espera > b.espera);
}

void resuelveCaso(PriorityQueue<registro> &cola, int espera) {
	char tipo;
	string nombre;
	int gravedad;

	cin >> tipo;

	if (tipo == 'I') {
		cin >> nombre >> gravedad;
		cola.push({ nombre, gravedad, espera });
	}
	else { //ha aparecido un medico
		cout << cola.top().nombre << "\n";
		cola.pop();
	}
}

int main() {

	int numEventos;
	cin >> numEventos;

	while (numEventos != 0) {

		PriorityQueue<registro> cola;

		while (numEventos--) {
			resuelveCaso(cola, numEventos);
		}

		cout << "---\n";

		cin >> numEventos;
	}

	return 0;
}