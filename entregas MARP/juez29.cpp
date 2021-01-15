#include <iostream>
#include <string>
#include <climits>
#include <vector>

#include "PriorityQueue.h"
using namespace std;

struct Hora {
	int horaFin;
	int minFin;
	int horaIni;
	int minIni;
};

bool operator<(Hora const&a, Hora const&b) {
	return a.horaFin < b.horaFin || (a.horaFin == b.horaFin && a.minFin < b.minFin);
}

bool factible(Hora const&a, Hora const&b) {
	if (a.horaFin < b.horaIni) return true;
	if (a.horaFin == b.horaIni && a.minFin <= b.minIni) return true;
	return false;
}


Hora horaMin(int hora, int min, int duracion) {

	Hora rtr;
	rtr.horaIni = hora;
	rtr.minIni = min;

	duracion += min + 10; //Para comprar palomitas
	min = 0;

	while (duracion >= 60) {
		hora++;
		duracion -= 60;
	}

	min = duracion;

	rtr.horaFin = hora;
	rtr.minFin = min;

	return rtr;

}

bool resuelveCaso() {

	int numPeliculas;
	cin >> numPeliculas;

	if (numPeliculas == 0) return false;

	int count = 0; //numero de peliculas que ver
	Hora ocupado = {0, 0};

	PriorityQueue<Hora, less<Hora>> peliculas;
	
	int hora, min, duracion;
	char aux;
	for (int i = 0; i < numPeliculas; i++) {
		cin >> hora >> aux >> min >> duracion;

		peliculas.push(horaMin(hora, min, duracion));
	}
	
	for (int i = 0; i < numPeliculas; i++) {
		if (factible(ocupado, peliculas.top())) {
			count++;
			ocupado = peliculas.top();
		}
		peliculas.pop();
	}

	cout << count << "\n";

	return true;
}

int main() {

	while (resuelveCaso()) {}
	return 0;
}