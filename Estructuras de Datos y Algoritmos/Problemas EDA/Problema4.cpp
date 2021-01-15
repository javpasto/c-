#include <iostream>
#include <vector>
#include <math.h>
using namespace std;


class monomio {

private:
	int coeficiente;
	int exponente;

public:

	//Constructor generico
	monomio() {
		coeficiente = 0;
		exponente = 0;
	}


	monomio(int coeficiente, int exponente) {
		this->coeficiente = coeficiente;
		this->exponente = exponente;
	}


	//Observadoras
	int getCoeficiente() {
		return coeficiente;
	}


	int getExponente() {
		return exponente;
	}


	bool operator<(monomio const& that) {
		return (this->exponente < that.exponente);
	}


	bool operator==(monomio const& that) {
		return (this->exponente == that.exponente);
	}


	void operator=(monomio const&that) {
		this->coeficiente = that.coeficiente;
		this->exponente = that.exponente;
	}


	monomio operator+(monomio const&that) {
		return monomio(this->coeficiente + that.coeficiente, that.exponente);
	}


	void swap(monomio pol1, monomio pol2) {
		monomio aux = pol1;
		pol1 = pol2;
		pol2 = aux;
	}


	int valor(int var) {
		return coeficiente * pow(var, exponente);
	}

	void read(istream & i = cin) {
		int aux1, aux2;

		cin >> aux1 >> aux2;

		this->coeficiente = aux1;
		this->exponente = aux2;
	}

};


inline istream & operator>>(istream & entrada, monomio & mon) {
	mon.read(entrada);
	return entrada;
}



class polinomio {

private:
	vector<monomio> polinom;

public:

	//constructor generico
	polinomio() {	}


	//Ordena el polinomio por exponentes y los suma si encuentra iguales
	void sortPolinom() {
		
		for (int i = 0; i < polinom.size(); i++) {

			for (int j = i + 1; j < polinom.size(); j++) {
				//Si dos polinomios tienen el mismo exponente eliminamos uno de los dos y los sumamos
				if (polinom[i] == polinom[j]) {
					polinom[i] = polinom[i] + polinom[j];
					polinom.erase(polinom.begin() + j);
				}
				else if (polinom[j] < polinom[i]) {
					swap(polinom[j], polinom[i]);
				}

			}
			
		}

	}


	//Añade un monomio y ordena el polinomio
	void addMonomio(monomio newMonomio) {
		polinom.push_back(newMonomio);
	}


	int polinomResult(int var) {
		int sum = 0;

		for (int i = 0; i < polinom.size(); i++) {
			sum += polinom[i].valor(var);
		}

		return sum;
	}


	void read(istream & i = cin) {
		monomio aux;

		cin >> aux;

		if (!cin) return;
		while (aux.getExponente() != 0 || aux.getCoeficiente() != 0) {
			this->addMonomio(aux);
			cin >> aux;
		}

		this->sortPolinom();
	}

};


inline istream & operator>>(istream & entrada, polinomio & pol) {
	pol.read(entrada);
	return entrada;
}



int main() {

	int numCasos, aux;

	while (cin.peek() != EOF) {
		polinomio pol;

		cin >> pol;

		if (!cin) return 0;

		cin >> numCasos;

		for (int i = 0; i < numCasos; i++) {
			cin >> aux;

			cout << pol.polinomResult(aux) << " ";
		}

		cout << endl;
	}


	return 0;
}