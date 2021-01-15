//Grupo U Javier Pastor

#include <iostream>
using namespace std;

typedef int tvector[9999];

int funcion(const tvector& vector, int n);

int main() {
	int casosDePrueba;

	cin >> casosDePrueba;

	for (int i = 0; i < casosDePrueba; i++) {
		int n;
		tvector vector;

		cin >> n;

		for (int i = 0; i < n; i++) { cin >> vector[i]; }

		cout << funcion(vector, n) << endl;
	}

	return 0;
}

int funcion(const tvector& vector, int n) {
	int p = 0;
	bool found = false;

	while (!found && p < n) {
		int maxV1 = vector[0], minV2 = vector[n - 1], counter = 0;
		bool wrong = false;

		while (!wrong && !found && counter < n) {

			if (counter <= p)
				if (maxV1 < vector[counter]) { maxV1 = vector[counter]; }

			if (n - counter > p + 1)
				if (minV2 > vector[n - counter - 1]) { minV2 = vector[n - counter - 1]; }

			if (maxV1 > minV2) { wrong = true; }

			counter++;
		}

		if (!wrong) { found = true; }

		p++;
	}

	return p - 1;
}