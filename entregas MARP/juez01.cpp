#include <iostream>
#include <string>
#include <climits>

#include "bintree_eda.h"
using namespace std;

int recursion(bintree<int> const& arbol, int &maxT, int &minT);
string resolver(bintree<int> const& arbol);

template <typename T>
bintree<T> readTree(T vacio){
    T raiz;
    cin >> raiz;
    if (raiz == vacio) return {};
    else    {
        auto iz = leerArbol(vacio);
        auto dr = leerArbol(vacio);
        return {iz, raiz, dr};
    }
    
}

string resolver(bintree<int> const& tree) {

	int aux1 = 0, aux2 = 0;
    int aux = recursion(tree, aux1, aux2);
    if (aux != -1) return "SI";
    else return "NO";

}

//First Height
//Second Max
//Third Min
int recursion(bintree<int> const& tree, int &maxT, int &minT){

	//Caso base
	if (tree.empty()) {
		maxT = 0;
		minT = INT_MAX;
		return 0;
	}

	tree.root();

	int maxL, minL, maxR, minR;

	int leftH = recursion(tree.left(), maxL, minL);
	int rightH = recursion(tree.right(), maxR, minR);

	tree.root();

	if (leftH == -1 || rightH == -1) return -1; //Algun subarbol ha fallado las condiciones
	if (tree.root() <= maxL && maxL != 0) return -1; //El maximo del arbol de la izquierda es mayor que la raiz
    if (tree.root() >= minR && minR != INT_MAX) return -1; //El minimo del arbol de la derecha es menor que la raiz
    if (leftH > rightH + 1 || rightH > leftH + 1) return -1; //La diferencia de alturas es mayor que uno


	maxT = max(tree.root(), maxR);
	minT = min(tree.root(), minL);

	return (1 + max(leftH, rightH));

}


void resuelveCaso() {

    bintree<int> tree = readTree(-1);

    string sol = resolver(tree);

    cout << sol << "\n";

}

int main() {
    int numCasos;
    cin >> numCasos;

    for (int i = 0; i < numCasos; ++i)  resuelveCaso();

    return 0;
}