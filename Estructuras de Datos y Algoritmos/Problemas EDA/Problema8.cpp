#include <stdexcept>  // std::domain_error
#include <iostream>
using namespace std;

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

	void print(ostream & o = cout) const {
		queue<T> aux(*this);

		for (int i = 0; i < this->nelems; i++) {
			o << aux.front() << " ";
			aux.pop();
		}

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

	void duplicateNodos() {
		//La cola original esta vacia
		if (this->empty()) {
			prim = ult = nullptr;
			nelems = 0;
		}
		else {
			Nodo * act = this->prim; // Recorre la cola
			Nodo * copy = new Nodo(act->elem); // Nodo copiado

			while (act->sig != nullptr) {

				copy->sig = act->sig;
				act->sig = copy;
				act = act->sig;
				act = act->sig;

				copy = new Nodo(act->elem);

				nelems++;
			}

			act->sig = copy;
			ult = copy;
			nelems++;
		}
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

};


template <class T>
class colaDup {

private:

	queue<T> cola;


public:

	//Duplica la lista
	void duplicate() {

		cola.duplicateNodos();

		/*
		queue<T> colaOriginal(this->cola);
		queue<T> nuevaCola;
		int aux = colaOriginal.size();

		//Duplicamos la lista	
		for (int i = 0; i < aux; i++) {
			nuevaCola.push(colaOriginal.front());
			nuevaCola.push(colaOriginal.front());
			colaOriginal.pop();
		}

		this->cola.copia(nuevaCola);
		*/
	}

	void print(ostream & o = cout) const {
		cola.print(o);
	}

	void read(istream & i = cin) {
		T aux;
		cin >> aux;

		while (aux != 0) {
			cola.push(aux);
			cin >> aux;
		}
	}

};


template <class T>
inline ostream & operator<<(ostream & salida, colaDup<T> const & cola) {
	cola.print(salida);
	return salida;
}


template <class T>
inline istream & operator>>(istream & salida, colaDup<T> & cola) {
	cola.read(salida);
	return salida;
}


void resuelveCaso(colaDup<int> & cola) {
	cola.duplicate();
}


int main() {

	while (cin.peek() != EOF) {
		colaDup<int> cola;

		cin >> cola;
		resuelveCaso(cola);
		cout << cola << endl;

	}

	return 0;
}