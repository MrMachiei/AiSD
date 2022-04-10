#include <iostream>
#include <time.h>

class Graph_MS{ //macierz_sasiedztwa
private:
	int V, E, **macierz;
public:
	Graph_MS(int v, int e);
	bool istnieje(int x, int y);
	void dodaj_luk(int x, int y);
	void usun_luk(int x, int y);
	void nastepniki(int v);
	void poprzedniki(int v);
	int stopien(int v);
	void wypisz();
	void Euler(int u);
	void permutuj(int t[], int V);
	void Hamilton();
	void Hamilton2(int v, int *stos,int *visited, int dlugosc, bool *czy);
	~Graph_MS();
};
Graph_MS* generuj_graf(int n, int p, int tryb); // 0 - Euler, 1 - Hamilton
bool in(int dane[], int V);
void permutacja(int t[], int V);