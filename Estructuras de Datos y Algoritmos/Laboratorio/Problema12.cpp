//Javier Pastor Doble Grado 2º Grupo U
#include <iostream>

using namespace std;

const int VECTOR = 10000;

typedef int tVector[VECTOR];

int encontrarIntervalo(const tVector &vector, int n, int altura, int &inicioIntervalo);

int main() {
	int n, altura, casosDePrueba;

	cin >> casosDePrueba;

	for (int i = 0; i < casosDePrueba; i++) {
		int inicioIntervalo, finalIntervalo;
		tVector vector;

		cin >> n >> altura;

		for (int j = 0; j < n; j++){
			cin >> vector[j];
		}

		finalIntervalo = encontrarIntervalo(vector, n, altura, inicioIntervalo);

		cout << inicioIntervalo << " " << finalIntervalo << endl;

	}

	return 0;
}


int encontrarIntervalo(const tVector &vector, int n, int altura, int &inicioIntervalo) {
	bool enIntervalo = false;

	int intervaloActual = 0, nuevoIntervalo = 0;
	int auxiliarInicio = 0, auxiliarFinal = 0;

	int finalIntervalo = 0;
	inicioIntervalo = 0;

	for (int i = 0; i < n; i++) {

		if (enIntervalo) {
			if (vector[i] > altura) {
				auxiliarFinal = i;
				nuevoIntervalo += 1;
			}
			else {
				enIntervalo = false;
				if (intervaloActual < nuevoIntervalo) {
					inicioIntervalo = auxiliarInicio;
					finalIntervalo = auxiliarFinal;
					intervaloActual = nuevoIntervalo;
				}
			}
		}
		else {
			if (vector[i] > altura) {
				enIntervalo = true;
				auxiliarInicio = i;
				auxiliarFinal = i;
				nuevoIntervalo = 1;
			}

		}

	}

	if (nuevoIntervalo == n) {
		inicioIntervalo = auxiliarInicio;
		finalIntervalo = auxiliarFinal;
	}


	return finalIntervalo;
}

//El coste de la solucion es de orden n debido a que solo recorremos una vez el array entero.