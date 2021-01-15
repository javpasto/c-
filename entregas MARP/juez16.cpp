#include <iostream>
#include <string>
#include <climits>

#include "Grafo.h"
#include "PriorityQueue.h"
using namespace std;

struct numCalc {
	int result;
	int dist;
};

//Solo nos importa la ordenacion por niveles a si q da igual si esta uno antes q otro
bool operator<(numCalc const&a, numCalc const&b) {
	return a.dist < b.dist || (a.dist == b.dist && a.result > b.result);
}

numCalc createNumCalc(int result, int dist) {
	numCalc rtr;
	rtr.result = result;
	rtr.dist = dist;
	return rtr;
}

int bfs(int start, int target) {

	PriorityQueue<numCalc> cola;

	cola.push(createNumCalc(start, 0));
	
	while (!cola.empty()) {
		
		numCalc top = cola.top();
		cola.pop();

		if (top.result == target) return top.dist;

		cola.push(createNumCalc((top.result + 1) % 10000, top.dist + 1));
		cola.push(createNumCalc((top.result * 2) % 10000, top.dist + 1));
		cola.push(createNumCalc((top.result / 3) % 10000, top.dist + 1));
		
	}
}

bool resuelveCaso() {

	int start, target;
	cin >> start >> target;

	if (!cin) return false;

	cout << bfs(start, target) << "\n";

	return true;
}

int main() {

	while (resuelveCaso()) {}
	return 0;
}