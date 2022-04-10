#include "graphs.h"

int main(){
	int v,e,x,y;
	std::cin >> v >> e;
	Graph_MI p(v,e);
	for(int i = 0; i < e; i++){
		std::cin >> x >> y;
		p.dodaj_luk(x,y);
	}
	p.wypisz();
	p.usun_luk(8,9);
	p.wypisz();
	p.stopien(9);
	return 0;
}