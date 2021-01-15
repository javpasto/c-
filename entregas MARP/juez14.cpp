#include <iostream>
#include <string>
#include <climits>

#include "Grafo.h"
using namespace std;


void mark(Grafo &G, int v, bool marked[], int &count, bool conected[]) {

	marked[v] = true;
	count++;

	for (auto e : G.ady(v)) {
		if (!marked[e]) {
			mark(G, e, marked, count, conected);
		}
	}

	conected[v] = true;
}

bool resuelveCaso() {

	int usuarios, grupos;
	cin >> usuarios >> grupos;

	if (!cin) return false;

	Grafo G(usuarios);

	while (grupos--) {
		int amigosGrupo;
		cin >> amigosGrupo;

		int anterior = -1;
		int siguiente;

		//No hace falta dibujar todas las aristas, basta con que esten conectados los amigos
		for (int i = 0; i < amigosGrupo; i++) {
			cin >> siguiente;
			if (anterior != -1)	G.ponArista(anterior - 1, siguiente - 1);
			anterior = siguiente;
		}

	}

	bool *marked = new bool[G.V()];
	int *tamGrupo = new int[G.V()];
	bool *conected = new bool[G.V()];

	for (int i = 0; i < G.V(); i++) {
		conected[i] = false;
		marked[i] = false;
		tamGrupo[i] = 1;
	}

	// Miramos el tamaño de las componentes conexas
	for (int v = 0; v < G.V(); v++) {
		int count = 0;
		if (!marked[v]) {
			mark(G, v, marked, count, conected);

			int max = 0;
			for (int i = 0; i < G.V() && max <= count; i++) {
				if (conected[i]) {
					max++;
					tamGrupo[i] = count;
					conected[i] = false;
				}
			}
		}

		cout << tamGrupo[v] << " ";
	}

	cout << "\n";

	return true;
}

int main() {

	while (resuelveCaso()) {}

	return 0;
}
