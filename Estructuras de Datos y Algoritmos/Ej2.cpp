#include <iostream>
using namespace std;


class fecha {

private:
	int day;
	int month;
	int year;

public:
	fecha() {}

	fecha(int day, int month, int year) {
		this->day = day;
		this->month = month;
		this->year = year;
	}

	//Lee una fecha
	void read() {
		char aux;
		cin >> this->day >> aux >> this->month >> aux >> this->year;
	}

};


//He usado treemap, unordered map y cola

//NO HE PODIDO PROBARLO YA QUE NO HE CONSEGUIDO ENCONTRAR LA FUNCION DE RESUELVE CASO QUE NOS DABAIS EN EL EXAMEN
class tienda {

	using nameCli = string;
	using nameProd = string;
	using numUni = int;

private:
	//El par es para guardar el total de un producto
	unordered_map<nameProd, pair<map<fecha, numUni>, numUni>> almacen;

	unordered_map<nameProd, queue<pair<nameCli, numUni>>> listaEspera;

public:

	queue<string> adquirir(string COD, fecha F, int CANT) { //O(log A)

		queue<string> clientesAtendidos;
		auto it = listaEspera.find(COD);
		if (it == listaEspera.end()) {
			//No hay clientes esperando

			this->agregarProdAlmacen(COD, F, CANT);

		}
		else {
			//Hay clientes esperando
			int cant = CANT;
			while (it->valor.size() > 0 & it->valor.front().second < cant) {
				clientesAtendidos.push(it->valor.front().first); //Añadimos el nombre por cada cliente atendido
				cant -= it->valor.front().second;
				it->valor.pop();
			}

			if (cant > 0) {
				this->agregarProdAlmacen(COD, F, cant); //Si hemos conseguido vender a toda la Lista de espera nos guardamos el sobrante
			}
		}

		return clientesAtendidos;
	}

	void agregarProdAlmacen(string name, fecha f, int cant) { //O(log A)

		auto it = almacen.find(name);
		if (it == almacen.end()) {
			//No existe el producto

			map<fecha, numUni> aux;
			aux.insert({ f, cant });
			almacen.insert({ name,{ aux, cant } });
		}
		else {
			//El producto ya existe
			it->valor.first.insert({ f, cant });
			it->valor.second += cant;
		}

	}

	pair<bool, fecha> vender(string COD, string CLI) { //O(1)

		auto it = almacen.find(COD);
		if (it == almacen.end()) {
			//Añadimos al cliente a la lista de espera ya que no está el producto en el almacen

			auto itL = listaEspera.find(COD);
			if (itL == listaEspera.end()) {
				//No existe la lista de espera para ese producto
				queue<pair<nameCli, numUni>> aux;
				aux.push({ CLI, 1 });
				listaEspera.insert({ COD, aux });
			}
			else {
				itL->valor.push({ CLI, 1 });
			}

			return{ false, fecha() };
		}
		else {
			//El producto esta en el almacen

			//No quedan unidades del productoen el almacen
			if (it->valor.second == 0) {
				almacen.erase(COD);
				return vender(COD, CLI); //Si quedan 0 unidades en el almacen, borramos COD del almacen y llamamos otra vez a la función
			}

			it->valor.first.begin()->valor -= 1;
			it->valor.second -= 1; //Restamos 1 a los totales

			fecha fechaVendida = it->valor.first.begin()->clave;

			if (it->valor.first.begin()->valor == 0) {
				it->valor.first.erase(it->valor.first.begin()->clave); //Borramos el elemento si no quedan articulos
			}
			if (it->valor.second == 0) {
				almacen.erase(COD);
			}

			return{ true, fechaVendida };
		}

	}

	int cuantos(string COD) { //O(1)

		auto it = almacen.find(COD);
		if (almacen.end() == it) return 0; //No existe el producto en el almacen
		return it->valor.second;

	}

	bool hay_esperando(string COD) { //O(1)

		auto it = listaEspera.find(COD);
		if (listaEspera.end() == it) return false;
		if (it->valor.size() == 0) return false;
		return true;

	}

};


int main() {



	return 0;
}