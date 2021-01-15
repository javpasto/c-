#include <iostream>
using namespace std;


void funRecursiva(long long raiz, int maxDigitos, int posicion, int limit);


void escribePolidivisible(long long raiz, int maxDigitos) {

	int digitosRaiz = 0;
	long long aux = raiz;

	while (aux > 0) {
		digitosRaiz++;
		aux /= 10;
	}

	funRecursiva(raiz, maxDigitos, digitosRaiz, digitosRaiz);

}


void funRecursiva(long long raiz, int maxDigitos, int posicion, int limit) {


	if (posicion > maxDigitos) {
		return;
	}

	if (raiz % posicion == 0) {
		cout << raiz << endl;
		funRecursiva(raiz*10, maxDigitos, posicion + 1, limit);
	}

	if ((raiz + 1) % 10 != 0) {

		if (posicion == limit) {
			cout << "---\n";
		}
		else {
			funRecursiva(raiz + 1, maxDigitos, posicion, limit);
		}

	}
	else return;

}


/*

PRE = { n > 0, alturaMax >= 0 }

proc arboles (v[0..n), output[0, 1) de nat, n, alturaMax : nat)

POST = { output = {i, j} & maximoSegmento(v, j, i) }

maximoSegmento(v, ini, fin, alturaMax) = { valid = ((Para todo)i, j : 0 <= j <= i < n & segmentoCumpleAltura(v, j, i, alturaMax) : i - j <= fin - ini) }

segmentoCumpleAltura(v, ini, fin, alturaMax) = { valid = ((Para todo)i : ini <= i <= fin : v[i] >= alturaMax) }

INVARIANTE = { i < n - 1 }

FUNCION COTA -> n - i

*/


int main() {

	long long raiz;
	int maxDigitos;

	while (cin.peek() != EOF) {

		maxDigitos = 0;

		cin >> raiz >> maxDigitos;

		if (maxDigitos != 0) {

			escribePolidivisible(raiz, maxDigitos);

		}

	}

	return 0;
}