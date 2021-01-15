#include <iostream>
using namespace std;

int main(){
	int n = 0, k, count = 0, numberSeries, constant = 0, prevConstant, i = 0;
	cin >> numberSeries;
	while (numberSeries > 0){

		while (n >= 0){
			k = n;
			cin >> n;
			prevConstant = constant;
			constant = n - k;

			if ((constant != prevConstant) && (i > 1) && (n != -1))
				count++;
			i++;
		}
		i = 0;
		cout << count << " " << k + prevConstant << endl;
		numberSeries--;
		n = numberSeries - 1;
		count = 0;
	}
		return 0;
}