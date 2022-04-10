#include "graphs.h"
#include <time.h>

int main(){
	srand(time(NULL));
	int v,e;
	clock_t start, end;
	//std::cin >> v >> e;
	Graph_MS *p;
	for(int i = 3; i < 15; i+=1){
		p = generuj_graf(i,10,1);
		//p->wypisz();
		//std::cout << "Cykl Eulera";
		start = clock();
		int *stos = new int[v];
		int *vis = new int[v];
		//if(p->Hamilton2(1,stos, 0)) std::cout << "YES\n";
		bool czy = 0;
		p->Hamilton2(1, stos, vis, 0,&czy);
		//std::cout << std::endl;
		end = clock();
		std::cout << i << "," <<double(end-start)/CLOCKS_PER_SEC << std::endl;
		delete[] stos;
		delete[] vis;
		delete p;
	}
	/*std::cout << "Cykl Hamiltona -> ";
	p->Hamilton();
	std::cout << std::endl;*/
	//delete p;
	return 0;
}