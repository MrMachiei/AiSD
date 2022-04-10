#include "plecak.h"
#include <ctime>

int main(){
	clock_t start, end;
	srand(time(NULL));
	Plecak *x;
	x = new Plecak(1000,2,6,2,15,8,40000);
	//x->wypisz();
	start = clock();
	x->maksymalizuj();
	end = clock();
	cout << "Czas: " << (double) (end-start)/CLOCKS_PER_SEC << endl;
	//x->wypiszMaks();
	//x->DUAL();
	//x->wypiszDUAL();
	delete x;
}




















































//©M.J.W.2020