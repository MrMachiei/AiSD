#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(){
	srand(time(NULL));
	fstream dane;
	int k = 40;
	for(int ile = 20000000; ile <= 100000000; ile += 10000000){
	dane.open("Dane3/dane" + to_string(k) + ".txt", ios::out);
	int n = ile;
	if(!dane.good()) cout << "IT WENT WRONG!";
	dane << n << "\n";
	int x;
	for(int i = 0; i < n; i++){
		x = ((rand() % (10000)));
		dane << x << " ";
	}
	dane.close();
	k += 1;
}
	return 0;
}