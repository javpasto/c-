#include <iostream>
#include <string>
#include <climits>

#include "PriorityQueue.h"
using namespace std;

struct grupoInstrumentos {
	int numMiembros;
	int numPartituras;
	int grupoMayor;
};


bool operator>(grupoInstrumentos const&a, grupoInstrumentos const&b) {
	return a.grupoMayor > b.grupoMayor || (a.grupoMayor == b.grupoMayor && a.numPartituras < b.numPartituras);
}

bool operator<(grupoInstrumentos const&a, grupoInstrumentos const&b) {
	return a.grupoMayor < b.grupoMayor || (a.grupoMayor == b.grupoMayor && a.numPartituras > b.numPartituras);
}


bool resuelveCaso() {

	int numPartituras, numInstrumentos;
	cin >> numPartituras >> numInstrumentos;

	if (!cin) return false;

	PriorityQueue<grupoInstrumentos, greater<grupoInstrumentos>> cola;

	int instrumentos;

	numPartituras -= numInstrumentos; //Se garantiza al menos una partitura por instrumento

	while (numInstrumentos--) {
		cin >> instrumentos;
		cola.push({ instrumentos, 1, instrumentos });
	}

	while (numPartituras--) {
		auto e = cola.top();
		cola.pop();
		e.numPartituras++;
		if (e.numMiembros % e.numPartituras == 0) e.grupoMayor = e.numMiembros / e.numPartituras;
		else e.grupoMayor = (e.numMiembros / e.numPartituras) + 1;
		cola.push(e);
	}

	cout << cola.top().grupoMayor << "\n";

	return true;
}

int main() {

	while (resuelveCaso()) {}
	return 0;
}