#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Horas {

	private:
		int horas;
		int minutos;
		int segundos;

	public:

		//constructor
		Horas() {

			char aux;

			cin >> this->horas >> aux >> this->minutos >> aux >> this->segundos;

			if (horas > 23 || horas < 0 || minutos > 59 || minutos < 0 || segundos > 59 || segundos < 0) {
				throw exception();
			}

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

		const bool operator<(Horas const& that) const{
			return (this->segundos + this->minutos * 60 + this->horas * 60 * 60) <=
				(that.segundos + that.minutos * 60 + that.horas * 60 * 60);
		}

};


string checkHora(Horas horaCheck, vector<Horas> horas, int trenesNum) {
	string rtr = "NO";

	for (int i = 0; i < trenesNum; i++) {
		if (horaCheck < horas[i]) {
			return horas[i].toString() + "\n";
		}
	}

	return rtr + "\n";
}


int main() {

	int trenesNum, horasNum;

	cin >> trenesNum >> horasNum;

	while (trenesNum != 0 && horasNum != 0) {

		vector <Horas> horas;

		for (int i = 0; i < trenesNum; i++) {
			Horas aux2 = Horas();
			horas.push_back(aux2);
		}

		for (int i = 0; i < horasNum; i++) {
			try {
				Horas horaCheck = Horas();
				cout << checkHora(horaCheck, horas, trenesNum);
			}
			catch (exception e) {
				cout << "ERROR" << endl;
			}
		}

		cout << "---" << endl;


		cin >> trenesNum >> horasNum;
	}

	return 0;
}