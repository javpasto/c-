#include <iostream>
#include <math.h>
using namespace std;

const int MARGEN = 2;

class complejo {

private:
	float a;
	float b;

public:

	complejo(float x, float y) {
		this->a = x;
		this->b = y;
	}


	//Constructor generico
	complejo() {
		this->a = 0;
		this->b = 0;
	}


	complejo operator+(complejo const &that) {
		complejo aux;

		aux.a = this->a += that.a;
		aux.b = this->b += that.b;

		return aux;
	}


	complejo operator*(complejo const&that) {
		complejo aux;

		aux.a = this->a*that.a - this->b*that.b;
		aux.b = this->a*that.b + this->b*that.a;

		return aux;
	}


	void operator=(complejo const&that) {
		this->a = that.a;
		this->b = that.b;
	}


	//Devuelve el modulo de un complejo
	float mod() {
		return sqrt((this->a + this->b)*(this->a + this->b));
	}


	void read(istream & i = cin) {
		float x, y;

		cin >> x >> y;

		this->a = x;
		this->b = y;
	}

};


//Lee un numero complejo
inline istream & operator >>(istream & entrada, complejo & complejo) {
	complejo.read(entrada);
	return entrada;
}


//Funcion recursiva
bool resuelveCaso(complejo sum, complejo original, int iteraciones, int margen) {

	//Caso base
	if (iteraciones < 0) {
		return true;
	}

	//Caso base
	if (sum.mod() > margen) {
		return false;
	}

	else {
		resuelveCaso((sum * sum) + original, original, iteraciones - 1, margen);
	}

}


int main() {

	int casos, iteraciones;
	complejo comple;

	cin >> casos;

	for (int i = 0; i < casos; i++) {

		cin >> comple >> iteraciones;

		//Complejo vacio para iniciar la sucesion z0 = 0
		complejo aux;

		if (resuelveCaso(aux, comple, iteraciones, MARGEN)) cout << "SI" << endl;
		else cout << "NO" << endl;

	}

	return 0;
}