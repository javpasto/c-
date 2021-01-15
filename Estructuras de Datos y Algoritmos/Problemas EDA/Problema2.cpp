#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class hora {

	private:
		int horas;
		int minutos;
		int segundos;

	public:

		//constructor
		hora(int horas, int minutos, int segundos) {

			this->horas = horas;
			this->minutos = minutos;
			this->segundos = segundos;

			check();

		}

		//Constructor para que el compilador no se queje
		hora() { }

		void read(istream& i = cin) {
			int horas;
			int minutos;
			int segundos; 
			char aux;

			cin >> horas >> aux >> minutos >> aux >> segundos;

			*this = hora(horas, minutos, segundos);
		}


		void check() {
			if (horas > 23 || horas < 0 || minutos > 59 || minutos < 0 || segundos > 59 || segundos < 0) {
				throw exception();
			}
		}


		//Observadores
		int getHoras() {
			return this->horas;
		}
		int getMinutos() {
			return this->minutos;
		}
		int getSegundos() {
			return this->segundos;
		}


		//Convierte una hora en segundos
		int horaToSeg() const{
			return this->segundos + this->minutos * 60 + this->horas * 60 * 60;
		}


		//Convierte segundos en hora
		hora segToHora(int seg) {
			hora rtr;

			rtr.horas = seg / (60 * 60);
			rtr.minutos = (seg - rtr.horas*60*60) / 60;
			rtr.segundos = seg - rtr.horas*60*60 - rtr.minutos*60;

			return rtr;
		}


		const string toString() const{
			
			string rtr = "";

			if (horas < 10) rtr += "0";
			rtr += to_string(horas) + ":";

			if (minutos < 10) rtr += "0";
			rtr += to_string(minutos) + ":";

			if (segundos < 10) rtr += "0";
			rtr += to_string(segundos);

			return rtr;
		}


		const bool operator<(hora const& that) const{
			return (this->segundos + this->minutos * 60 + this->horas * 60 * 60) <=
				(that.segundos + that.minutos * 60 + that.horas * 60 * 60);
		}


		//Copia la hora
		void operator=(hora const& that) {
			this->horas = that.horas;
			this->minutos = that.minutos;
			this->segundos = that.segundos;
		}


		//Devuelve true si son iguales
		bool operator==(hora const& that) {
			if (this->horaToSeg() == that.horaToSeg())
				return true;
			return false;
		}


		//Suma dos horas
		hora operator+(hora const& that){
			int auxSeg1 = this->horaToSeg();
			int auxSeg2 = that.horaToSeg();

			hora aux = segToHora(auxSeg1 + auxSeg2);

			aux.check(); //Lanza excepcion si la hora excede el dia actual

			return aux;
		}

};


class pelicula {

private:
	hora inicio;
	hora duracion;
	string titulo;

public:

	//Constructor por defecto
	pelicula() { }


	//Constructor
	pelicula(hora inicio, hora duracion, string titulo) {
		this->inicio = inicio;
		this->duracion = duracion;
		this->titulo = titulo;
	}


	//Devuelve la hora de salida de la pelicula
	hora horaFinal() {
		return this->inicio + this->duracion;
	}


	bool operator<(pelicula& that) {

		if (this->horaFinal() == that.horaFinal()) {
			if (this->titulo < that.titulo)
				return true;
		}
		else if (this->horaFinal() < that.horaFinal())
			return true;

		return false;

	}

	void operator=(pelicula const& that) {
		this->inicio = that.inicio;
		this->duracion = that.duracion;
		this->titulo = that.titulo;
	}


	//Lee una pelicula
	void read(istream& i = cin) {
		int horas;
		int minutos;
		int segundos;
		char aux;
		string titulo;

		cin >> horas >> aux >> minutos >> aux >> segundos;
		this->inicio = hora(horas, minutos, segundos);
		
		cin >> horas >> aux >> minutos >> aux >> segundos;
		this->duracion = hora(horas, minutos, segundos);

		getline(cin, titulo);

		this->titulo = titulo;
	}


	string toString() {
		return this->horaFinal().toString() + " " + this->titulo;
	}

};



//Entrada de hora
inline istream & operator>>(istream & entrada, hora & hora) {
	hora.read(entrada);
	return entrada;
}

//Entrada de pelicula
inline istream & operator>>(istream & entrada, pelicula & pelicula) {
	pelicula.read(entrada);
	return entrada;
}


/*
string checkHora(hora horaCheck, vector<hora> horas, int trenesNum) {
	string rtr = "NO";

	for (int i = 0; i < trenesNum; i++) {
		if (horaCheck < horas[i]) {
			return horas[i].toString() + "\n";
		}
	}

	return rtr + "\n";
}
*/


void resuelveCaso(vector<pelicula> & peliculas, int peliculasNum) {
	string rtr = "";
	pelicula aux;

	sort(peliculas.begin(), peliculas.end());


	/*
	for (int i = 0; i < peliculasNum; i++) {
		for (int j = i + 1; j < peliculasNum; j++) {
			if (peliculas[j] < peliculas[i]) {
				aux = peliculas[i];
				peliculas[i] = peliculas[j];
				peliculas[j] = aux;
			}
		}
		rtr += peliculas[i].toString() + "\n";
	}

	return rtr;
	*/

}


int main() {

	int peliculasNum;

	cin >> peliculasNum;

	while (peliculasNum != 0) {

		vector <pelicula> peliculas;
		pelicula aux;

		for (int i = 0; i < peliculasNum; i++) {
			cin >> aux;
			peliculas.push_back(aux);
		}

		resuelveCaso(peliculas, peliculasNum);

		for (int i = 0; i < peliculasNum; i++) {
			cout << peliculas[i].toString() << endl;
		}

		cout << "---" << endl;


		cin >> peliculasNum;
	}

	return 0;
}