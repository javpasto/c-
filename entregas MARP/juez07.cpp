#include <iostream>
#include <string>
#include <climits>

#include "PriorityQueue.h"
using namespace std;

struct tarea {
	int empieza;
	int termina;
	int periodo;
};

bool operator>(tarea const&a, tarea const&b) {
	return a.empieza > b.empieza || (a.empieza == b.empieza && a.periodo > b.periodo);
}

bool operator<(tarea const&a, tarea const&b) {
	return a.empieza < b.empieza || (a.empieza == b.empieza && a.periodo < b.periodo);
}

bool resuelveCaso(PriorityQueue<tarea> &cola, int limit) {

	bool rtr = false;

	while (!cola.empty() && cola.top().empieza < limit) {

		auto e = cola.top();
		cola.pop();
		if (cola.empty()) return false; //Por si solo queda un elemento en la cola
		if (cola.top().empieza < e.termina && cola.top().empieza < limit) return true; //Hay un conflicto
		if (e.periodo != 0) { //Solo volvemos a anadir la tarea si es periodica
			e.empieza += e.periodo;
			e.termina += e.periodo;
			cola.push(e);
		}
	}

	return rtr;
}

int main() {

	while (true) {

		int tareasUnicas, tareasPeriodicas, minutosConflicto;
		cin >> tareasUnicas >> tareasPeriodicas >> minutosConflicto;
		
		if (!cin) return 0;

		PriorityQueue<tarea> cola;

		int empTarea, terTarea, periodo;

		//Leemos los datos de entrada de las tareas
		while (tareasUnicas--) {
			cin >> empTarea >> terTarea;
			cola.push({ empTarea, terTarea, 0 });
		}
		while (tareasPeriodicas--) {
			cin >> empTarea >> terTarea >> periodo;
			cola.push({ empTarea, terTarea, periodo });
		}

		if (resuelveCaso(cola, minutosConflicto)) cout << "SI\n";
		else cout << "NO\n";
	}

	return 0;
}