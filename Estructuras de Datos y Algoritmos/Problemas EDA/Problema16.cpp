#include <iostream>
#include <string>
using namespace std;


class persona {

private:

	string nombre;
	int edad;

public:

	//Constructor
	persona(string nombre, int edad) : nombre(nombre), edad(edad) {}

	persona() {}

	string getNombre() {
		return nombre;
	}

	int getEdad() {
		return edad;
	}

	bool operator<(int num) {
		if (this->getEdad() < num) return true;
		return false;
	}

	bool operator>(int num) {
		if (this->getEdad() > num) return true;
		return false;
	}

};


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


#ifndef list_eda_h
#define list_eda_h

#include <stdexcept>
#include <cassert>

//#include "deque_eda.h"

template <class T>
class list : public deque<T> {
protected:
	using Nodo = typename deque<T>::Nodo;
public:

	// constructor: lista vacía
	list() {}

	// consultar el elemento en la posición ind, si existe (numeradas desde 0)
	T const& at(int ind) const {
		if (ind >= this->nelems)
			throw std::out_of_range("posicion fuera de la lista");

		Nodo * aux = this->fantasma->sig;
		for (int i = 0; i < ind; ++i)
			aux = aux->sig;

		return aux->elem;
	}

protected:
	template <class Apuntado>
	class Iterador {
		// puntero al nodo actual del recorrido
		Nodo * act;
		// puntero al nodo fantasma (para saber cuándo estamos fuera)
		Nodo * fan;
	public:

		Iterador() : act(nullptr), fan(nullptr) {}

		// para acceder al elemento apuntado
		Apuntado & operator*() const {
			if (act == fan) throw std::out_of_range("fuera de la lista");
			return act->elem;
		}

		// para acceder a un método del elemento apuntado
		// it->metodo() en vez de (*it).metodo()
		Apuntado * operator->() const {
			return &(operator*());
		}

		Iterador & operator++() { // ++ prefijo (recomendado)
			if (act == fan) throw std::out_of_range("fuera de la lista");
			act = act->sig;
			return *this;
		}

		Iterador operator++(int) { // ++ postfijo
			Iterador ret(*this);
			operator++();
			return ret;
		}

		bool operator==(Iterador const& that) const {
			return act == that.act && fan == that.fan;
		}

		bool operator!=(Iterador const& that) const {
			return !(*this == that);
		}

	private:
		// para que list pueda construir objetos del tipo iterador
		friend class list;

		// constructora privada
		Iterador(Nodo * ac, Nodo * fa) : act(ac), fan(fa) {}
	};

public:
	/*
	 Iteradores que permiten recorrer la lista pero no cambiar sus elementos.
	 */
	using const_iterator = Iterador<T const>;

	// devuelven un iterador constante al principio de la lista
	const_iterator cbegin() const {
		return const_iterator(this->fantasma->sig, this->fantasma);
	}
	const_iterator begin() const {
		return cbegin();
	}

	// devuelven un iterador constante al final del recorrido y fuera de este
	const_iterator cend() const {
		return const_iterator(this->fantasma, this->fantasma);
	}
	const_iterator end() const {
		return cend();
	}

	/*
	 Iteradores que permiten recorrer la lista y cambiar sus elementos.
	 */
	using iterator = Iterador<T>;

	// devuelve un iterador al principio de la lista
	iterator begin() {
		return iterator(this->fantasma->sig, this->fantasma);
	}

	// devuelve un iterador al final del recorrido y fuera de este
	iterator end() {
		return iterator(this->fantasma, this->fantasma);
	}

	// inserta un elemento delante del apuntado por el iterador it
	// (it puede estar apuntado detrás del último)
	// devuelve un iterador al nuevo elemento
	iterator insert(iterator const& it, T const& elem) {
		assert(this->fantasma == it.fan); // comprueba que el iterador es de esta lista
		Nodo * nuevo = this->inserta_elem(elem, it.act->ant, it.act);
		return iterator(nuevo, this->fantasma);
	}

	// elimina el elemento apuntado por el iterador (debe haber uno)
	// devuelve un iterador al siguiente elemento al borrado
	iterator erase(iterator const& it) {
		assert(this->fantasma == it.fan); // comprueba que el iterador es de esta lista
		if (it.act == this->fantasma)
			throw std::out_of_range("fuera de la lista");
		iterator next(it.act->sig, this->fantasma);
		this->borra_elem(it.act);
		return next;
	}
};

#endif // list_eda_h


class Predicate {

public:

	int minEdad;
	int maxEdad;

	int getMin() { return minEdad; }
	int getMax() { return maxEdad; }

	Predicate(int edad[]) : minEdad(edad[0]), maxEdad(edad[1]) {}
	Predicate() {}

};


class myList : public list<persona> {

	using iterator = list::iterator;

public:

	template <class Predicate>
	void operator()(Predicate pred) {
		this->remove_if(pred);
	}

	template <class Predicate>
	void remove_if(Predicate pred) {

		iterator it;

		for (it = this->begin(); it != this->end();) {

			if (*it < pred.getMin() || *it > pred.getMax()) {
				it = this->erase(it);
			}
			else
				it++;
		}

	}

	void print() {

		for (persona per : *this) {
			cout << per.getNombre().substr(1) << endl; //Para eliminar el espacio
		}

		cout << "---" << endl;

	}

};




int main() {

	int numPer;
	int edad[1];

	cin >> numPer >> edad[0] >> edad[1];

	while (numPer != 0) {

		myList personas;
		persona aux;
		int age;
		string name;

		for (int i = 0; i < numPer; i++) {
			cin >> age;
			getline(cin, name);
			personas.push_back(persona(name, age));
		}

		personas(Predicate(edad));

		personas.print();

		cin >> numPer >> edad[0] >> edad[1];
	}

	return 0;
}