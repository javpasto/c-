#include <iostream>
#include <string>
#include <climits>

#include "Grafo.h"
//#include "Queue.h"
using namespace std;


void dfs(Grafo &G, int nodo, int lvl[], int TTL, int &count, bool marked[]) {

	if (lvl[nodo] < TTL || !marked[nodo]) {
		if (!marked[nodo]) count++; //Estaba sin marcar
		lvl[nodo] = TTL;

		marked[nodo] = true;

		if (TTL - 1 >= 0) {
			for (auto e : G.ady(nodo)) {
				if (lvl[e] < TTL - 1 || !marked[e])
					dfs(G, e, lvl, TTL - 1, count, marked);
			}
		}
	}

}

/*
void bfs(Grafo &G, int nodo, int lvl[], int TTL, int &count, bool marked[]) {
	Queue<int> q = new Queue<int>();
	marked[nodo] = true;
	queue.enqueue(nodo);
	while (!q.isEmplty()) {
		int v = q.dequeue();
		for (int w : G.ady(v)) {
			if (!marked[w]) {
				marked[w] = true;
				q.enqueue(w);
			}
		}
	}
}
*/

bool resuelveCaso() {

	int numNodos, conexiones;
	cin >> numNodos >> conexiones;

	if (!cin) return false;

	Grafo G(numNodos + 1); //nodo 0 presente pero sin conexiones
	int origen, destino;

	while (conexiones--) {
		cin >> origen >> destino;
		G.ponArista(origen, destino);
	}

	int numConsultas;
	cin >> numConsultas;

	while (numConsultas--) {
		int nodo, TTL;
		cin >> nodo >> TTL;

		int *lvl = new int[G.V()];
		bool *marked = new bool[G.V()];

		for (int i = 0; i < G.V(); i++) {
			lvl[i] = -1;
			marked[i] = false;
		}

		int count = 0;

		dfs(G, nodo, lvl, TTL, count, marked);

		cout << G.V() - 1 - count << "\n";
	}

	cout << "---\n";

	return true;
}

int main() {

	while (resuelveCaso()) {}
	return 0;
}