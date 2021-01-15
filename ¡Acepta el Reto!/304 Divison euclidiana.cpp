#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int divNum; //For the number of divisions
	int a, b, q, r = 0;
	bool aB, bB; //To see if their are negative or positive

	cin >> divNum;

	for (int i = 0; i < divNum; i++){
		cin >> a;
		cin >> b;
		if (a >= 0)
			aB = true;
		else
			aB = false;
		if (b > 0)
			bB = true;
		else
			bB = false;

		if (b == 0)
			cout << "DIV0" << endl;
		else{
			if ((aB == true) && (bB == true)){
				q = a / b;
				r = a - (b * q);
				cout << q << " " << r << endl;
			}
			if ((aB == true) && (bB == false)){
				q = a / b;
				r = a - (b * q);
				cout << q << " " << r << endl;
			}
			if ((aB == false) && (bB == true)){
				q = a / b;
				q--;
				r = a - (b * q);
				if (r == b){
					q++;
					r = 0;
				}
				cout << q << " " << r << endl;
			}
			if ((aB == false) && (bB == false)){
				q = a / b;
				q++;
				r = a - (b * q);
				if (r == -b){
					q--;
					r = 0;
				}
				cout << q << " " << r << endl;
			}
		}
	}
	return 0;
}