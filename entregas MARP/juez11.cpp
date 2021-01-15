#include <iostream>
#include <string>
#include <climits>

#include "Grafo.h"
using namespace std;
/*
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
*/

void mark(Grafo &G, int v, bool marked[], int &count) {

	marked[v] = true;
	count++;

	for (auto e : G.ady(v)) {
		if (!marked[e]) {
			mark(G, e, marked, count);
		}
	}
}


void resuelveCaso() {

	int numVertices, numAristas;
	cin >> numVertices >> numAristas;

	Grafo G(numVertices + 1);
	int origen, destino;

	while (numAristas--) {
		cin >> origen >> destino;
		G.ponArista(origen, destino);
	}

	bool *marked = new bool[G.V()];
	int maxCount = 0;

	for (int i = 0; i < G.V(); i++) {
		marked[i] = false;
	}

	// Miramos el tamaño de las componentes conexas
	for (int v = 0; v < G.V(); v++) {
		int count = 0;
		if (!marked[v]) mark(G, v, marked, count);
		if (count > maxCount) maxCount = count;
	}

	cout << maxCount << "\n";
}

int main() {

	int numCasos;
	cin >> numCasos;

	while (numCasos--) resuelveCaso();

	return 0;
}