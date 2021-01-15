#include <iostream>
#include <string>
#include <climits>

#include "PriorityQueue.h"
using namespace std;

/*
bool operator>(tarea const&a, tarea const&b) {
	return a.empieza > b.empieza || (a.empieza == b.empieza && a.periodo > b.periodo);
}

bool operator<(tarea const&a, tarea const&b) {
	return a.empieza < b.empieza || (a.empieza == b.empieza && a.periodo < b.periodo);
}
*/

bool resuelveCaso() {

	int numEventos, input;
	cin >> numEventos;

	if (!cin) return false;

	PriorityQueue<int, greater<int>> cola1;
	PriorityQueue<int, less<int>> cola2;

	while (numEventos--) {
		cin >> input;

		if (input == 0) {
			if (cola1.empty()) cout << "ECSA ";
			else {
				cout << cola1.top() << " ";
				cola1.pop();
				if (cola1.size() < cola2.size()) {
					cola1.push(cola2.top());
					cola2.pop();
				}
			}
		}
		else {
			cola1.push(input);

			if (cola1.size() > cola2.size() + 1) {
				cola2.push(cola1.top());
				cola1.pop();
			} //Se nivelan

			if (!cola2.empty())
				while (cola1.top() > cola2.top()) {
					cola1.push(cola2.top());
					cola2.pop();
					cola2.push(cola1.top());
					cola1.pop();
				}

			/*
			else if (cola2.top() > input) {
				if (cola1.size() > cola2.size()) {
					cola2.push(cola1.top());
					cola1.pop();
				}
				else
					cola1.push(input);
			}
			else { //cola2.top() < input
				if (cola2.size() >= cola1.size()) {
					cola1.push(cola2.top());
					cola2.pop();
				}
				else cola2.push(input);
			}
			*/
		}
	}

	/*
	cout << "\n\n";

	while (cola1.size() > 0) {
		cout << cola1.top() << " ";
		cola1.pop();
	}

	cout << "\n";

	while (cola2.size() > 0) {
		cout << cola2.top() << " ";
		cola2.pop();
	}
	*/

	cout << "\n";

	return true;
}

int main() {

	while (resuelveCaso()) {}
	return 0;
}