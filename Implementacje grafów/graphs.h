#include <iostream>
#include <iomanip>
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
	void stopien(int v);
	void wypisz();
	~Graph_MS();
};

class Graph_MI{ //macierz_sasiedztwa
private:
	int V, E,**macierz, obecny;
public:
	Graph_MI(int v, int e);
	int istnieje(int x, int y);
	void dodaj_luk(int x, int y);
	void usun_luk(int x, int y);
	void nastepniki(int v);
	void poprzedniki(int v);
	void stopien(int v);
	void wypisz();
	~Graph_MI();
};

class Graph_LN{ //lista_następników
private:
	int V, E;
	struct Lista{
		int key;
		Lista *next;
		Lista *prev;
	};
	Lista *lista;
public:
	Graph_LN(int v, int e);
	bool istnieje(int x, int y);
	void dodaj_luk(int x, int y);
	void usun_luk(int x, int y);
	void nastepniki(int v);
	void poprzedniki(int v);
	void stopien(int v);
	void wypisz();
	~Graph_LN();
};

class Graph_LP{ //lista_poprzednikow
private:
	int V, E;
	struct Lista{
		int key;
		Lista *next;
		Lista *prev;
	};
	Lista *lista;
public:
	Graph_LP(int v, int e);
	bool istnieje(int y, int x);
	void dodaj_luk(int y, int x);
	void usun_luk(int y, int x);
	void nastepniki(int v);
	void poprzedniki(int v);
	void stopien(int v);
	void wypisz();
	~Graph_LP();
};
class Graph{
private:
	struct Lista{
		int key;
		Lista *next;
		Lista *prev;
	};
	int V, E, **m_sasiedztwa, **m_incydencji, *topologicznie, miejsce;
	Lista *l_nastepnikow, *l_poprzednikow;
	short *kolor;
public:
	Graph(int v, int e);
	void znajdz_bialy(int v);
	void sort_topologiczne();
	void wypisz_macierz();
	void wypisz_listy();
	~Graph();
};