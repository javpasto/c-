#include <iostream>
using namespace std;

//Structures
typedef struct {

	int piscina;
	int barreno;
	int perdida;

} tData;

//Prototypes
int numeroViajes(tData yo);

int main(){
	tData yo, vecino;
	int viajesYo, viajesVecino;

	cin >> yo.piscina >> yo.barreno >> yo.perdida >> vecino.piscina >> vecino.barreno >> vecino.perdida;

	do {

		viajesYo = numeroViajes(yo);
		viajesVecino = numeroViajes(vecino);

		if (viajesVecino == -1)
			viajesVecino = viajesYo + 1;
		if (viajesYo == -1)
			viajesYo = viajesVecino + 1;

		if (viajesYo == viajesVecino)
			cout << "EMPATE	" << viajesYo << endl;
		else if (viajesYo > viajesVecino)
			cout << "VECINO " << viajesVecino << endl;
		else
			cout << "YO " << viajesYo << endl;

		cin >> yo.piscina >> yo.barreno >> yo.perdida >> vecino.piscina >> vecino.barreno >> vecino.perdida;

	} while ((yo.piscina > 0) && (vecino.piscina > 0));

	return 0;
}

int numeroViajes(tData yo){
	int viajes = 0, trayecto;

	trayecto = yo.barreno - yo.perdida;

	if (trayecto <= 0)
		viajes = -1;
	else if (trayecto >= yo.piscina)
		viajes = 1;
	else{
		viajes = yo.piscina / trayecto;
		if (viajes * trayecto < yo.piscina)
			viajes++;
	}

	return viajes;
}


//Revisar respuesta incorrecta. Se comporta perfectamente con los casos de ejemplo y deberia funcionar con el resto