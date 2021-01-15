#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include <string>
using namespace std;


template <class T>
class set {

public:

	set() : contador(0), capacidad(8), datos(new T[capacidad]) {}

	set(set<T> const& other) {
		copia(other);
	}

	~set() { delete[] this->datos; }

	//Los inserta manteniendo orden de menos a mayor sin repeticiones
	void insertSort(T e, int maxElem) {
		if (contador == capacidad)
			amplia();
		if (contador == 0) { //Si no hay ningun dato introducimos uno
			datos[contador] = e;
			contador++;
		}
		for (int i = 0; i < contador; ++i) {
			if (datos[i] == e) return; //No hace nada ya que no queremos insertar datos repetidos
			else if (e < datos[i]) {
				shiftArrayRight(i); //Mueve los elementos a la derecha
				datos[i] = e; //Inserta el elemento en la posicion que deberia estar
				contador++;
				return;

			}
			else if (i == contador - 1) { //El ultimo elemento se ha alcanzado y era menor a si que el nuevo ira al final
				datos[contador] = e;
				contador++;
				return;
			}
		}
	}

	void insert(T e, int maxElem) {
		insertSort(e, maxElem);
		//Si el vector tiene mas de los elementos maximos elimina el primero que sera el mas pequeño
		if (contador == maxElem + 1)
			eraseMin();
	}

	bool contains(T e) const {
		int i = 0;
		while (i < contador && datos[i] != e)
			++i;
		return i < contador;
	}

	int size() const {
		return contador;
	}

	//Elimina el elemento mas pequeño
	void eraseMin() {
		shiftArrayLeft();
		contador--;
	}

	void erase(T e) {
		int i = 0;
		while (i < contador && datos[i] != e)
			++i;
		if (i < contador) {
			datos[i] = datos[contador - 1];
			--contador;
		}
		else
			throw std::domain_error("El elemento no está");
	}

	bool empty() const {
		return contador == 0;
	}

	void getElem(int place) {
		cout << datos[place];
	}

	/*
	void coutArray() {
		for (int i = 0; i < contador; i++) {
			cout << datos[i] << " ";
		}

		cout << endl;
	}
	*/

	set<T> & operator=(set<T> const& other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}


private:

	int contador;
	int capacidad;
	T * datos;

	void amplia() {
		T * nuevos = new T[2 * capacidad];
		for (int i = 0; i < capacidad; ++i)
			nuevos[i] = datos[i];
		delete[] datos;
		datos = nuevos;
		capacidad *= 2;
	}

	void libera() { delete[] datos; }

	void copia(set<T> const& other) {
		capacidad = other.capacidad;
		contador = other.contador;
		datos = new T[capacidad];
		for (int i = 0; i < contador; ++i)
			datos[i] = other.datos[i];
	}

	//Mueve los elementos del array a la derecha desde la posicion dada
	void shiftArrayRight(int begin) {
		for (int i = this->contador - 1; i >= begin; i--) {
			datos[i + 1] = datos[i];
		}
	}

	//Mueve todos los elementos del array a la izquierda
	void shiftArrayLeft() {
		for (int i = 0; i < contador; i++) {
			datos[i] = datos[i + 1];
		}
	}

};



template <class T>
void resuelveCaso(set<T> & vector, int numElem) {

	for (int i = vector.size() - numElem; i < vector.size(); i++) {
		vector.getElem(i);
		cout << " ";
	}

}


int main() {

	char type;
	int numElem;

	while (cin.peek() != EOF) {

		cin >> type >> numElem;

		if (!cin) return 0;

		if (type == 'N') {
			set<int> aux;
			int auxiliar;
			cin >> auxiliar;
			while (auxiliar != -1) {
				aux.insert(auxiliar, numElem);
				cin >> auxiliar;
			}
			resuelveCaso(aux, numElem);
			cout << endl;

		}
		else {
			set<string> aux;
			string auxiliar;
			cin >> auxiliar;
			while (auxiliar != "FIN") {
				aux.insert(auxiliar, numElem);
				cin >> auxiliar;
			}
			resuelveCaso(aux, numElem);
			cout << endl;

		}

	}

	return 0;
}