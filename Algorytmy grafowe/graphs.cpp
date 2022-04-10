#include "graphs.h"

	//macierz sasiedztwa
	Graph_MS::Graph_MS(int v, int e){
		V = v;
		E = 0;
		//przygotowanie struktur danych
		macierz = new int*[v];
		for(int i = 0; i < V; i++){
			macierz[i] = new int[v];
			for(int j = 0; j < V; j++){
				macierz[i][j] = 0;
			}
		}
	}
	bool Graph_MS::istnieje(int x, int y){
		if (macierz[x-1][y-1] == 1) return 1;
		return 0;
	}
	void Graph_MS::dodaj_luk(int x, int y){
		if(istnieje(x,y)){
			std::cout << "Łuk " << x << " " << y <<" istnieje!\n";
			return;
		}else{
			macierz[x-1][y-1] = 1;
			macierz[y-1][x-1] = -1;
		}
		E++;
	}
	void Graph_MS::usun_luk(int x, int y){
		if(istnieje(x,y)){
			macierz[x-1][y-1] = 0;
			macierz[y-1][x-1] = 0;
		}else{
			std::cout << "Łuk nie istnieje!\n";
			return;
		}
		E--;
	}
	void Graph_MS::nastepniki(int v){
		std::cout << "Lista nastepników: " << v;
		for(int i = 0; i < V; i++){
			if(macierz[v-1][i] == 1){
				std::cout  << " -> " << i+1;
			}
		}
		std::cout << "\n";
	}
	void Graph_MS::poprzedniki(int v){
		std::cout << "Lista poprzednikow: " << v;
		for(int i = 0; i < V; i++){
			if(macierz[i][v-1] == 1){
				std::cout  << " -> " << i+1;
			}
		}
		std::cout << "\n";
	}
	int Graph_MS::stopien(int v){
		int st = 0;
		for(int i = 0; i < V; i++){
			if(macierz[v-1][i] == 1 && v-1 == i){
				st+=2;
				continue;
			}
			if(macierz[v-1][i] == 1) st++;
		}
		return st;
	}
	void Graph_MS::wypisz(){
		std::cout << "Macierz sąsiedztwa: \n";
		for(int i = 0; i < V; i++){
			for(int j = 0; j < V; j++){
				std::cout << macierz[i][j] << " ";
			}
			std::cout << std::endl;
		std::cout << std::endl;
		}
	}
	Graph_MS::~Graph_MS(){
		for(int i = 0; i < V; i++){
			delete[] macierz[i];
		}
		delete [] macierz;

	}
	void Graph_MS::Euler(int u){
		for(int j = 0; j < V; j++){
			if(macierz[u-1][j] == 1){
				usun_luk(u,j+1);
				Euler(j+1);
			}
		}
		//std::cout << " -> " << u;
	}
	void Graph_MS::permutuj(int *t, int V){
		if( V < 2) return;
		int r,l, k;
		r = V-1;
		while((r > 0) && (t[r-1] >= t[r])) r--;
		if( r > 0) {
			l = V;
			while((l > 0) && (t[l-1] <= t[r-1])) l--;
		}
		if((l > 0) && (r > 0)){
			k = t[r-1];
			t[r-1] = t[l-1];
			t[l-1] = k;
		}
		for(r++, l = V; r < l; r++, l--){
			k = t[r-1];
			t[r-1] = t[l-1];
			t[l-1] = k;
		}
	}
	int sptr = 0;
	void Graph_MS::Hamilton2(int v, int *stos, int *visited, int dlugosc, bool *czy){
		if (*czy) return;
		stos[sptr++] = v;
		if(sptr < V){
			visited[v-1] = 1;
			for(int i = 0; i < V; i++){
				if(istnieje(v, i+1)){
					if(visited[i] == 0) Hamilton2(i+1, stos, visited, dlugosc+1, czy);
				}
			}
			visited[v-1] = 0;
		}else{
			for(int i = 0; i < V; i++){
				std::cout << stos[i] << " -> ";
			}
			std::cout << stos[0] << std::endl;
			*czy = 1;
		}
		sptr--;
	}
	void Graph_MS::Hamilton(){
		int *dane = new int[V];
		for(int i = 0; i < V; i++) dane[i] = i;
		unsigned long long ile_perm = 1;
		//for(unsigned long long i = 0; i < V; i++) ile_perm *= (i+1);
		int i = 0;
		while(1){
			int j = 0;
			for(j; j < V-1; j++){
				if(!istnieje(dane[j]+1, dane[j+1]+1)){
					break;
				}
			}
			if(j == V-1){
				if(istnieje(dane[j]+1,dane[0]+1)){
					std::cout << dane[0]+1;
					for(int k = 1; k < V;k++) std::cout << " -> " << dane[k]+1;
					std::cout << " -> "<< dane[0]+1;
					delete[] dane;
					return;
				}
			}
			permutuj(dane, V);
			i++;
		}
		std::cout << " -> "<< dane[0]+1;
		delete[] dane;
	}
	Graph_MS* generuj_graf(int n, int p, int tryb){
		int *dane = new int[n];
		for(int i = 0; i < n; i++){
			dane[i] = n-i-1;
		}
		//permutacja(dane, n);
		for(int i = 0; i < n; i++) std::cout << dane[i]+1 << " , ";
		std::cout<<std::endl;
		int ile = n*n*p/100;
		Graph_MS *wynik = new Graph_MS(n,ile);
		int x, y;
		int i = 0;
		for(int j = 0; j < n-1; j++,i+=2){
			//std::cout << "ERROR!\n";
			wynik->dodaj_luk(dane[j]+1, dane[j+1]+1);
		}
		if(tryb == 1){
			i+=2;
			wynik->dodaj_luk(dane[n-1]+1,dane[0]+1);
		}
		for(i; i < ile; i++){
			do{
				x = rand() % n + 1;
				y = rand() % n + 1;
			}while(wynik->istnieje(x,y));
			wynik->dodaj_luk(x,y);
			if(x != y) i++;
		}
		if(tryb == 0){
			int stopien;
			for(int i = 0; i < n; i++){
				stopien = wynik->stopien(i+1);
				if(stopien % 2 == 1){
					for(int j = 0; j < n; j++){
						if(i==j) continue;
						if(!wynik->istnieje(i+1,j+1)){
							wynik->dodaj_luk(i+1, j+1);
							break;
						}else{
							for(int k = 0; k < n-1; k++){
								if((dane[k] == j && dane[k+1] == i) || (dane[k] == i && dane[k+1] == j)) continue;
							}
							wynik->usun_luk(i+1, j+1);
							break;
						}
					}
				}
			}
		}
		delete[] dane;
		return wynik;
	}
	bool in(int dane[], int V, int x){
		for(int i = 0; i < V; i++) if (dane[i] == x) return true;
		return false;
	}
	void permutacja(int dane[], int V){
		int r;
		for(int i = 0; i < V; i++){
			do{
				r = rand() % V;
			}while(in(dane, V, r));
		
			dane[i] = r;
		}
	}