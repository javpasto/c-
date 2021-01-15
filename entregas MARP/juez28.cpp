#include <iostream>
#include <string>
#include <climits>
#include <vector>

#include "PriorityQueue.h"
using namespace std;


bool resuelveCaso() {

	int ciudades;
	cin >> ciudades;

	if (!cin) return false;

	int count = 0; //Cuenta ciudades no defendibles

	PriorityQueue<int, greater<int>> enemigos;
	PriorityQueue<int, greater<int>> aliados;

	
	int in;
	for (int i = 0; i < ciudades; i++) {
		cin >> in;
		enemigos.push(in);
	}
	for (int i = 0; i < ciudades; i++) {
		cin >> in;
		aliados.push(in);
	}

	for (int i = 0; i < ciudades; i++) {
		if (enemigos.top() <= aliados.top()) {
			aliados.pop();
			count++;
		}
		enemigos.pop();
	}

	cout << count << "\n";

	return true;
}

int main() {

	while (resuelveCaso()) {}
	return 0;
}