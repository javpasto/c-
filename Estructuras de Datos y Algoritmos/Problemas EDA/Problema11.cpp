#ifndef queue_eda_h
#define queue_eda_h

#include <stdexcept>  // std::domain_error

template <class T>
class queue {
protected:

	/*
	 Nodo que almacena internamente el elemento (de tipo T),
	 y un puntero al nodo siguiente, que puede ser nullptr si
	 el nodo es el último de la lista enlazada.
	 */
	struct Nodo {
		Nodo() : sig(nullptr) {}
		Nodo(T const& elem, Nodo * si = nullptr) : elem(elem), sig(si) {}
		T elem;
		Nodo * sig;
	};

	// punteros al primer y último elemento
	Nodo * prim;
	Nodo * ult;

	// número de elementos en la cola
	int nelems;

public:

	// constructor: cola vacía
	queue() : prim(nullptr), ult(nullptr), nelems(0) {}

	// destructor
	~queue() {
		libera();
	}

	// constructor por copia
	queue(queue<T> const& other) {
		copia(other);
	}

	// operador de asignación
	queue<T> & operator=(queue<T> const& other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	// añadir un elemento al final de la cola
	void push(T const& elem) {
		Nodo * nuevo = new Nodo(elem);

		if (ult != nullptr)
			ult->sig = nuevo;
		ult = nuevo;
		if (prim == nullptr) // la cola estaba vacía
			prim = nuevo;
		++nelems;
	}

	// consultar el primero de la cola
	T const& front() const {
		if (empty())
			throw std::domain_error("la cola vacia no tiene primero");
		return prim->elem;
	}

	// eliminar el primero de la cola
	void pop() {
		if (empty())
			throw std::domain_error("eliminando de una cola vacia");
		Nodo * a_borrar = prim;
		prim = prim->sig;
		if (prim == nullptr) // la cola se ha quedado vacía
			ult = nullptr;
		delete a_borrar;
		--nelems;
	}

	// consultar si la cola está vacía
	bool empty() const {
		return nelems == 0;
	}

	// consultar el tamaño de la cola
	int size() const {
		return nelems;
	}

protected:

	void libera() {
		while (prim != nullptr) {
			Nodo * a_borrar = prim;
			prim = prim->sig;
			delete a_borrar;
		}
		ult = nullptr;
	}

	// this está sin inicializar
	void copia(queue const& other) {
		if (other.empty()) {
			prim = ult = nullptr;
			nelems = 0;
		}
		else {
			Nodo * act = other.prim; // recorre la cola original
			Nodo * ant = new Nodo(act->elem); // último nodo copiado
			prim = ant;
			while (act->sig != nullptr) {
				act = act->sig;
				ant->sig = new Nodo(act->elem);
				ant = ant->sig;
			}
			ult = ant;
			nelems = other.nelems;
		}
	}
};

#endif // queue_eda_h

#include <iostream>
using namespace std;

template <class T>
class cola : public queue<T> {

public:

	void mezclarListas(cola<T> lista2) {
		
		int tam = this->size() + lista2.size();
		int counter = this->size();

		for (int i = 0; i < tam; i++) {
			if (lista2.size() == 0) {
				for (int j = i; j < tam; j++) {
					this->push(this->front());
					this->pop();
				}
				return;
			}
			else if (counter == 0) {
				while (lista2.size() > 0) {
					this->push(lista2.front());
					lista2.pop();
				}
				return;
			}
			else {
				if (this->front() <= lista2.front()) {
					this->push(this->front());
					this->pop();
					counter--; //Para llevar el tracking de la pista 1 de los elementos colocados de si misma
				}
				else {
					this->push(lista2.front());
					lista2.pop();
				}
			}
		}


	}

	void print() {
		queue<T> aux(*this);
		
		while (aux.size() > 0) {
			cout << aux.front() << " ";
			aux.pop();
		}

		cout << endl << endl << endl;
	}


private:



};

int main() {

	int numCasos;

	cin >> numCasos;

	for (int i = 0; i < numCasos; i++) {

		cola<int> lista1;
		cola<int> lista2;


		int aux;
		do
		{ 
			cin >> aux;
			if (aux != 0) lista1.push(aux);
		} while (aux != 0);

		do
		{
			cin >> aux;
			if (aux != 0) lista2.push(aux);
		} while (aux != 0);


		lista1.mezclarListas(lista2);

		lista1.print();

	}


	return 0;
}