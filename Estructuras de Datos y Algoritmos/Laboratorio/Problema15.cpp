//Javier Pastor Ramirez

#include <iostream>
using namespace std;

int fibonacci(int number);

int main() {
	int number;

	cin >> number;

	while (number >= 0) {
		cout << fibonacci(number) << endl;

		cin >> number;

		if (!cin) number = -1;
	}

	return 0;
}

int fibonacci(int number) { //No final
	int x = 0;

	if (number == 0) x = 0;
	else if (number == 1) x = 1;
	else x = fibonacci(number - 1) + fibonacci(number - 2);

	return x;
}