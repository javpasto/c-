#include <iostream>
#include <string>
#include <climits>

#include "PriorityQueue.h"
using namespace std;


struct registro {
	int momento;
	int id;
	int periodo;
};

bool operator<(registro const&a, registro const&b) {
	return a.momento < b.momento || (a.momento == b.momento && a.id < b.id);
}

bool resuelveCaso() {
	int usu;
	cin >> usu;

	if (usu == 0) return false;

	PriorityQueue<registro> cola;

	for (int i = 0; i < usu; i++) {
		int id_usu, periodo;
		cin >> id_usu >> periodo;
		cola.push({ periodo, id_usu, periodo });
	}

	int envios;
	cin >> envios;

	while (envios--) {
		auto e = cola.top();
		cola.pop();
		cout << e.id << "\n";
		e.momento += e.periodo;
		cola.push(e);
	}

	cout << "---\n";
	return true;
}

int main() {
	while (resuelveCaso()) {}
	return 0;
}