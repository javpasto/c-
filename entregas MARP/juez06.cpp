#include <iostream>
#include <string>
#include <climits>

#include "PriorityQueue.h"
using namespace std;

struct caja {
	int numCaja;
	int tiempoOcupada;
};

bool operator>(caja const&a, caja const&b) {
	return a.tiempoOcupada > b.tiempoOcupada || (a.tiempoOcupada == b.tiempoOcupada && a.numCaja > b.numCaja);
}

bool operator<(caja const&a, caja const&b) {
	return a.tiempoOcupada < b.tiempoOcupada || (a.tiempoOcupada == b.tiempoOcupada && a.numCaja < b.numCaja);
}

int resuelveCaso(PriorityQueue<caja> &cola) {
	int tiempoCliente;

	cin >> tiempoCliente;

	auto e = cola.top();
	cola.pop();
	e.tiempoOcupada += tiempoCliente;
	cola.push(e);

	return cola.top().numCaja;
}

int main() {

	int numCajas, numClientes;
	cin >> numCajas >> numClientes;

	while (numCajas != 0) {

		PriorityQueue<caja> cola;

		for (int i = 0; i < numCajas; i++) {
			cola.push({ i + 1, 0 }); //Creamos numCajas cajas todas con ocupación 0
		}

		int cajaAtendido;

		while (numClientes--) {
			cajaAtendido = resuelveCaso(cola);
		}

		cout << cajaAtendido<< "\n";

		cin >> numCajas >> numClientes;
	}

	return 0;
}