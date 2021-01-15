#include <iostream>
#include <string>
#include <climits>

#include "Matriz.h"
using namespace std;

struct Celda {
	char simbol;
	bool visited = false;
};


void adjCell(int i, int j, Matriz<Celda> &m, int &count, int filas, int columnas) {
	if (i < 0 || i >= filas || j < 0 || j >= columnas) return;
	if (m[i][j].simbol == '#' && !m[i][j].visited) {
		count++;
		m[i][j].visited = true;
		adjCell(i - 1, j, m, count, filas, columnas);
		adjCell(i + 1, j, m, count, filas, columnas);
		adjCell(i, j - 1, m, count, filas, columnas);
		adjCell(i, j + 1, m, count, filas, columnas);
	}
}

bool resuelveCaso() {

	int filas, columnas;
	cin >> filas >> columnas;

	if (!cin) return false;

	Celda cel = { ' ', false };

	Matriz<Celda> m = Matriz<Celda>(filas, columnas);

	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			cin >> m[i][j].simbol;
			m[i][j].visited = false;
		}
	}

	int maxCount = 0;
	int numManchas = 0;

	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (!m[i][j].visited) {
				if (m[i][j].simbol == '#') {
					int count = 0;
					adjCell(i, j, m, count, filas, columnas);
					numManchas++;
					if (count > maxCount) {
						maxCount = count;
					}
				}
				m[i][j].visited = true;
			}
		}
	}

	cout << numManchas << " " << maxCount << "\n";

	return true;
}

int main() {

	while (resuelveCaso()) {}

	return 0;
}