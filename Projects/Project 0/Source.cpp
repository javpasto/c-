//Test Proyect 0
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

//Prototype
double calculate();
int multipTable();
double convert();
double currency();

int main(){

	int option = 0, firstTime = 0;
	bool valid = false; //To make the menu.

	//If the number is not between 0 and 4, it will ask again to the user.
	while (valid == false){

		//To output a different mensaje the first time.
		if (firstTime == 0){

			valid = true;

			cout << "1 - Calculator" << endl << "2 - Multiplication Table" << endl
				<< "3 - Measure Converter" << endl << "4 - Currentcy Converter" << endl
				<< "0 - Exit" << endl << "Your choice: ";
			cin >> option;

			if (option > 4)
				valid = false;
			if (option < 0)
				valid = false;

			if (option == 1)
				calculate();
			if (option == 2)
				multipTable();
			if (option == 3)
				convert();
			if (option == 4)
				currency();
			else
				valid = false;
			if (option == 0)
				valid = true;
		}

		while ((firstTime >= 1) && (valid == false)){
			cout << "Select another option." << endl
				<< "1 - Calculator" << endl << "2 - Multiplication Table" << endl
				<< "3 - Measure Converter" << endl << "4 - Currentcy Converter" << endl
				<< "0 - Exit" << endl << "Your choice: ";
			cin >> option;

			valid = true;

			if (option > 4)
				valid = false;
			if (option < 0)
				valid = false;

			if (option == 1)
				calculate();
			if (option == 2)
				multipTable();
			if (option == 3)
				convert();
			if (option == 4)
				currency();
			else
				valid = false;
			if (option == 0)
				valid = true;
		}
		firstTime++;
	}
	return 0;
}

double calculate(){
// Lesson 2 - Exercise 19

	double op1, op2, result;
	char operat;
	cout << "Operand Operator Operand (0 to end): ";
	cin >> op1;
	while (op1 != 0) {
		cin >> operat >> op2;
		if (operat == '+') {
			result = op1 + op2;
		}
		if (operat == '-') {
			result = op1 - op2;
		}
		if (operat == '*')  {
			result = op1 * op2;
		}
		if (operat == '/') {
			result = op1 / op2;
		}
		cout << op1 << " " << operat << " " << op2
			<< " = " << result << endl;
		cout << "Operand Operator Operand (0 to end): ";
		cin.sync();
		cin >> op1;
	}
	return 0;
}

int multipTable(){
// Lesson 2 - Exercise 18

	int num, i;
	bool noVale = true;
	while (noVale) {
		cout << "Enter a number (1-100): ";
		cin >> num;
		if (num >= 1) {
			if (num <= 100) {
				noVale = false;
			}
		}
	}
	i = 1;
	while (i <= 10) {
		cout << setw(3) << i << "  x  "
			<< setw(4) << num << "  =  "
			<< setw(5) << i * num << endl;
		i++;
	}

	return 0;
}

double convert(){
	// Lesson 2 - Exercise 17

	const double CmPerInch = 2.54;
	const double MetersPerMile = 1609.344;
	const double LitersPerGallon = 4.5461;
	const double GramsPerOunce = 28.349523125;
	const double KgPerPound = 0.45359237;
	double measure, converted;
	char unit;
	string outputUnit;

	cout << "Admitted Units: inches (i), miles (m), Fahrenheit degrees(f), gallons (g), ounces (o) and pounds (p)." << endl;
	cout << "Enter a measure (quantity followed by a unit letter; 0 to end): ";
	cin >> measure;
	while (measure != 0) {
		cin >> unit;
		if (unit == 'i') {
			converted = measure * CmPerInch;
			outputUnit = "cm";
		}
		if (unit == 'm') {
			converted = measure * MetersPerMile;
			outputUnit = "m";
		}
		if (unit == 'f') {
			converted = (measure - 32) * 5 / 9;
			outputUnit = "C";
		}
		if (unit == 'g') {
			converted = measure * LitersPerGallon;
			outputUnit = "l";
		}
		if (unit == 'o') {
			converted = measure * GramsPerOunce;
			outputUnit = "gr";
		}
		if (unit == 'p') {
			converted = measure * KgPerPound;
			outputUnit = "kg";
		}
		cout << "Equivalent to " << converted << " " << outputUnit << endl;
		cout << "Enter a measure (quantity followed by a unit letter; 0 to end): ";
		cin >> measure;
	}

	return 0;
}

double currency(){

	//E(euro), D(dollar) and P(pound sterling)
	const double DtoE = 0.90476, EtoD = 1.10527,
				 DtoP = 0.65210, PtoD = 1.53352,
				 EtoP = 0.72065, PtoE = 1.38764;
	double quantity = 0, converted = 0;
	char unitOriginal, unitConverted;

	cout << "This program will transform into euros (E), dollars (D) and pounds (P) into euros, dollars and pounds. Enter 0 to end." << endl
		<< "Quantity = ";
	cin >> quantity;
	while (quantity != 0){
		cout << " ";
		cin >> unitOriginal;
		unitOriginal = toupper(unitOriginal);

		cout << " ";
		cin >> unitConverted;
		unitConverted = toupper(unitConverted);

		if (unitOriginal = 'D'){
			if (unitConverted = 'E')
				converted = quantity * DtoE;
			if (unitConverted = 'P')
				converted = quantity * DtoP;
			if (unitConverted = 'D')
				cout << "Choose a diferent unit from the first one." << endl;
		}
		if (unitOriginal ='E') {
			if (unitConverted = 'D')
				converted = quantity * EtoD;
			if (unitConverted = 'P')
				converted = quantity * EtoP;
			if (unitConverted = 'E')
				cout << "Choose a diferent unit from the first one." << endl;
		}
		if (unitOriginal = 'P') {
			if (unitConverted = 'D')
				converted = quantity * PtoD;
			if (unitConverted = 'E')
				converted = quantity * PtoE;
			if (unitConverted = 'P')
				cout << "Choose a diferent unit from the first one." << endl;
		}
		else
			cout << "the original unit and the converted unit has to be E,D or P only. Try again!";

		cout << converted << " " << unitConverted << endl;

		cout << "This program will transform into euros (E), dollars (D) and pounds (P) into euros, dollars and pounds. Enter 0 to end." << endl
			<< "Quantity = ";
		cin >> quantity;
	}
	return 0;
}