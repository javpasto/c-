#include <iostream>
using namespace std;

//Global Constants
const int DIM = 20;
const int DIM2 = 400;

//Strucst
typedef struct {

    int platos;
	int coronas;

} tGears;

typedef struct {

	double result;
	int platicos;
	int coronicas;

} tRelaciones;

//Array
typedef int tEngranajes[DIM];
typedef tRelaciones tPosibles[DIM2];

//Prototypes
void initEngranajes(tEngranajes &platos);
void initPosibles(tPosibles &posibles);
void sortLoop(tPosibles &posibles, tGears gears);
void dispayPosibles(tPosibles posibles, tGears gears);

int main(){
	tGears gears;
	tEngranajes platos, coronas;
	tPosibles posibles;

	cin >> gears.platos >> gears.coronas;

	do {
		initEngranajes(platos);
		initEngranajes(coronas);
		initPosibles(posibles);

		for (int i = 0; i < gears.platos; i++) {
			cin >> platos[i];
		}
		for (int i = 0; i < gears.coronas; i++) {
			cin >> coronas[i];
		}

		for (int i = 0; i < gears.platos; i++) {
			for (int j = 0; j < gears.coronas; j++) {
				posibles[j].platicos = platos[i];
				posibles[j].coronicas = coronas[j];
				posibles[j].result = (platos[j] / coronas[j]);
			}
		}
		
		sortLoop(posibles, gears);

		dispayPosibles(posibles, gears);

		cin >> gears.platos >> gears.coronas;
	} while ((gears.platos != 0) || (gears.coronas != 0));
	
	return 0;
}


void initEngranajes(tEngranajes &platos) {
	for (int i = 0; i < DIM; i++)
		platos[i] = 0;
}

void initPosibles(tPosibles &posibles) {
	for (int i = 0; i < DIM2; i++) {
		posibles[i].result = 0;
		posibles[i].platicos = 0;
		posibles[i].coronicas = 0;
	}
}

void sortLoop(tPosibles &posibles,tGears gears) {
	tRelaciones auxiliar;
	for (int j = 0; j < (gears.platos * gears.coronas) - 1; j++) {
		for (int i = 0; i < (gears.platos * gears.coronas) - 1; i++) {
			if (posibles[i].result > posibles[i + 1].result) {
				auxiliar = posibles[i];
				posibles[i] = posibles[i + 1];
				posibles[i + 1] = posibles[i];
			}
		}
	}
}

void dispayPosibles(tPosibles posibles, tGears gears) {
	for (int i = 0; i < (gears.coronas * gears.platos); i++)
		cout << posibles[i].platicos << "-" << posibles[i].coronicas << " ";
	cout << endl;
}