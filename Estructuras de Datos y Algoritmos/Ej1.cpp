#include <iostream>
using namespace std;

#ifndef deque_eda_h
#define deque_eda_h

#include <stdexcept>
#include <cassert>

template <class T>
class deque {
protected:
	/*
	Nodo que almacena internamente el elemento (de tipo T),
	y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	*/
	struct Nodo {
		Nodo() : ant(nullptr), sig(nullptr) {}
		Nodo(T const& elem, Nodo * ant, Nodo * sig) : elem(elem), ant(ant), sig(sig) {}
		T elem;
		Nodo * ant;
		Nodo * sig;
	};

	// puntero al nodo fantasma
	Nodo * fantasma;

	// número de elementos
	int nelems;

public:

	// constructor: cola doble vacía
	deque() : fantasma(new Nodo()), nelems(0) {
		fantasma->sig = fantasma->ant = fantasma; // circular
	}

	// destructor
	~deque() {
		libera();
	}

	// constructor por copia
	deque(deque<T> const& other) {
		copia(other);
	}

	// operador de asignación
	deque<T> & operator=(deque<T> const& that) {
		if (this != &that) {
			libera();
			copia(that);
		}
		return *this;
	}

	// añadir un elemento por el principio
	void push_front(T const& e) {
		inserta_elem(e, fantasma, fantasma->sig);
	}

	// añadir un elemento por el final
	void push_back(T const& e) {
		inserta_elem(e, fantasma->ant, fantasma);
	}

	// consultar el primer elemento de la dcola
	T const& front() const {
		if (empty())
			throw std::domain_error("la dcola vacia no tiene primero");
		return fantasma->sig->elem;
	}

	// consultar el último elemento de la dcola
	T const& back() const {
		if (empty())
			throw std::domain_error("la dcola vacia no tiene ultimo");
		return fantasma->ant->elem;
	}

	// eliminar el primer elemento
	void pop_front() {
		if (empty())
			throw std::domain_error("eliminando el primero de una dcola vacia");
		borra_elem(fantasma->sig);
	}

	// elminar el último elemento
	void pop_back() {
		if (empty())
			throw std::domain_error("eliminando el ultimo de una dcola vacia");
		borra_elem(fantasma->ant);
	}

	// consultar si la dcola está vacía
	bool empty() const {
		return nelems == 0;
	}

	// consultar el tamaño de la cola doble
	int size() const {
		return nelems;
	}

protected:

	void libera() {
		// primero rompemos la circularidad
		fantasma->ant->sig = nullptr;
		fantasma->ant = nullptr;
		while (fantasma != nullptr) {
			Nodo * a_borrar = fantasma;
			fantasma = fantasma->sig;
			delete a_borrar;
		}
	}

	void copia(deque<T> const& other) {
		fantasma = new Nodo();
		fantasma->sig = fantasma;
		fantasma->ant = fantasma;
		nelems = 0;

		// act recorre la cola que estamos copiando
		Nodo * act = other.fantasma->sig;
		while (act != other.fantasma) {
			push_back(act->elem);
			act = act->sig;
		}
	}

	// insertar un nuevo nodo entre anterior y siguiente
	Nodo * inserta_elem(T const& e, Nodo * anterior, Nodo * siguiente) {
		Nodo * nuevo = new Nodo(e, anterior, siguiente);
		anterior->sig = nuevo;
		siguiente->ant = nuevo;
		++nelems;
		return nuevo;
	}

	// eliminar el nodo n
	void borra_elem(Nodo * n) {
		assert(n != nullptr);
		n->ant->sig = n->sig;
		n->sig->ant = n->ant;
		delete n;
		--nelems;
	}
};

#endif // deque_eda_h

class resCas : deque<int> {

	using Nodo = deque<int>::Nodo;

private:


public:

	void entremezclar(resCas &other) {

		Nodo * anterior = this->fantasma->sig; //Apunta al primero de this
		Nodo * actual = other.fantasma->sig; //Apunta al primero de other
		Nodo * auxiliar;
		int sizeT = this->size();
		int sizeO = other.size();

		//Vamos cambiando las direcciones de ant y sig entremezclando las listas hasta que llegamos al final de una
		while (actual != this->fantasma && actual != other.fantasma) {

			auxiliar = anterior->sig;
			anterior->sig = actual;
			actual->ant = anterior;

			anterior = actual;
			actual = auxiliar;
		}

		//Si las listas son iguales
		if (sizeT == sizeO) {
			anterior->sig = this->fantasma;
			this->fantasma->ant = anterior;
		}
		//Si la lista original es mayor que la dada
		else if (sizeT > sizeO) {
			//Nada
		}
		//Si la lista dada es mayor que la original
		else {
			this->fantasma->ant = other.fantasma->ant;
			other.fantasma->ant->sig = this->fantasma;
		}

		other.fantasma->sig = nullptr;
	}

	void read() {
		int aux;
		int tam;
		cin >> tam;

		for (int j = 0; j < tam; j++) {
			cin >> aux;
			this->push_back(aux);
		}
	}

	void mostrarCola() {

		deque<int> aux(*this);

		while (aux.size() > 0) {
			cout << aux.front() << " ";
			aux.pop_front();
		}

		cout << endl;
	}

};


int main() {

	int numCasos;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++) {
		resCas cola1;
		resCas cola2;

		cola1.read();

		cola2.read();

		cola1.entremezclar(cola2);

		cola1.mostrarCola();
	}

	return 0;
}
