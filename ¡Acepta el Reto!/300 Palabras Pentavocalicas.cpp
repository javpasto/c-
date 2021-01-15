#include <iostream>
#include <cmath>
using namespace std;
#include <string>
#include <cctype>

//Global Constants
const int DIM = 30, ISPENTA = 5;

//Global types
typedef char tSequence [DIM];
typedef bool seqBool[ISPENTA];

//Prototypes

int main(){
	tSequence sequence;
	seqBool seqB;
	int wordNum;
	string str;

	cin >> wordNum;

	for (int k = 0; k < wordNum; k++){

		cin >> str;

		for (int i = 0; i < DIM; i++){
				
			str[sequence[i]];

			if (sequence[i] == 'a')
				seqB[0] = true;
			if (sequence[i] == 'e')
				seqB[1] = true;
			if (sequence[i] == 'i')
				seqB[2] = true;
			if (sequence[i] == 'o')
				seqB[3] = true;
			if (sequence[i] == 'u')
				seqB[4] = true;
			if (sequence[i] == '13'){
				i = DIM;
		}
	}
		if ((seqB[0] == true) && (seqB[1] == true) && (seqB[2] == true) && (seqB[3] == true) && (seqB[4] == true))
			cout << "SI" << endl;
		else
			cout << "NO" << endl;
	}
		return 0;
}