#include <iostream>
using namespace std;
#include <string>


string stringToCode(string input);
char charToCode(char character);
string letterToCode(char firstLetter);


int main(){
	string input, letter, solution;
	char firstLetter;

	cin >> input;

	do{

		firstLetter = input[0]; //To get the first letter of the word

		letter = letterToCode(firstLetter);

		solution = stringToCode(input);

		cout << input;

		if (solution == letter)
			cout << " OK" << endl;
		else
			cout << " X" << endl;

		input = " ";

		cin >> input;

	} while (input != " ");

	return 0;
}


string stringToCode(string input){
	string result;
	char character;
	int size;
	size = input.length();

	for (int i = 0; i <= size - 1; i++){
		character = input[i];
		character = tolower(character);
		character = charToCode(character);
		if (character != 'x')
			result += character;
	}

	return result;
}

char charToCode(char character){
	char result = 'x';

	character = tolower(character);

	if (character == 'o')
		result = '-';
	else if ((character == 'a') || (character == 'e') || (character == 'i') || (character == 'u'))
		result = '.';

	return result;
}

string letterToCode(char firstLetter){
	string result;

	firstLetter = tolower(firstLetter);

	if (firstLetter == 'a')
		result = ".-";
	else if (firstLetter == 'a')
		result = ".-";
	else if (firstLetter == 'b')
		result = "-...";
	else if (firstLetter == 'c')
		result = "-.-.";
	else if (firstLetter == 'd')
		result = "-..";
	else if (firstLetter == 'e')
		result = ".";
	else if (firstLetter == 'f')
		result = "..-.";
	else if (firstLetter == 'g')
		result = "--.";
	else if (firstLetter == 'h')
		result = "....";
	else if (firstLetter == 'i')
		result = "..";
	else if (firstLetter == 'j')
		result = ".---";
	else if (firstLetter == 'k')
		result = "-.-";
	else if (firstLetter == 'l')
		result = ".-..";
	else if (firstLetter == 'm')
		result = "--";
	else if (firstLetter == 'n')
		result = "-.";
	else if (firstLetter == 'o')
		result = "---";
	else if (firstLetter == 'p')
		result = ".--.";
	else if (firstLetter == 'q')
		result = "--.-";
	else if (firstLetter == 'r')
		result = ".-.";
	else if (firstLetter == 's')
		result = "...";
	else if (firstLetter == 't')
		result = "-";
	else if (firstLetter == 'u')
		result = "..-";
	else if (firstLetter == 'v')
		result = "...-";
	else if (firstLetter == 'w')
		result = ".--";
	else if (firstLetter == 'x')
		result = "-..-";
	else if (firstLetter == 'y')
		result = "-.--";
	else if (firstLetter == 'z')
		result = "--..";

	return result;
}