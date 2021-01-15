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

bool isCyclic(Grafo &G, int v, bool marked[], int parent, int &count) {

	marked[v] = true;
	count++;

	for (auto e : G.ady(v)) {
		if (!marked[e]) {
			if (isCyclic(G, e, marked, v, count)) return true;
		}
		else if (e != parent) return true;
	}

	return false;
}


bool resuelveCaso() {

	int numVertices, numAristas;
	cin >> numVertices >> numAristas;

	if (!cin) return false;

	Grafo G(numVertices);
	int origen, destino;

	while (numAristas--) {
		cin >> origen >> destino;
		G.ponArista(origen, destino);
	}

	bool *marked = new bool[G.V()];
	int count = 0;

	for (int i = 0; i < G.V(); i++) {
		marked[i] = false;
	}

	//Comporbamos que no hay ciclos || comprobamos que la componente conexa de 0 sea el grafo entero
	if (isCyclic(G, 0, marked, -1, count) || count != G.V()) {
		cout << "NO\n";
		return true;
	}

	cout << "SI\n";

	return true;
}

int main() {

	while (resuelveCaso()) {}
	return 0;
}