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
		if (macierz[x-1][y-1] != 0) return 1;
		return 0;
	}
	void Graph_MS::dodaj_luk(int x, int y){
		if(istnieje(x,y)){
			std::cout << "Łuk " << x << " " << y <<" istnieje!\n";
			return;
		}else{
			if(x==y){
				macierz[x-1][y-1] = 2;
				E++;
				return;
			}
			macierz[x-1][y-1] = 1;
			if (macierz[y-1][x-1] != 1) macierz[y-1][x-1] = -1;
		}
		E++;
	}
	void Graph_MS::usun_luk(int x, int y){
		if(istnieje(x,y)){
			if(macierz[y-1][x-1] == 1){
				macierz[x-1][y-1] = 0;
			}else{
				macierz[x-1][y-1] = 0;
				macierz[y-1][x-1] = 0;
			}
		}else{
			std::cout << "Łuk nie istnieje!\n";
			return;
		}
		E--;
	}
	//POPRAWIC
	void Graph_MS::nastepniki(int v){
		std::cout << "Lista nastepników: " << v;
		for(int i = 0; i < V; i++){
			if(macierz[v-1][i] == 1 || macierz[v-1][i] == 2){
				std::cout  << " -> " << i+1;
			}
		}
		std::cout << "\n";
	}
	void Graph_MS::poprzedniki(int v){
		std::cout << "Lista poprzednikow: " << v;
		for(int i = 0; i < V; i++){
			if(macierz[i][v-1] == 1 || macierz[v-1][i] == 2){
				std::cout  << " -> " << i+1;
			}
		}
		std::cout << "\n";
	}
	void Graph_MS::stopien(int v){
		int st_in = 0, st_out = 0;
		for(int i = 0; i < V; i++){
			if(macierz[v-1][i] == 2){
				st_in++;
				st_out++;
				continue;
			}
			if(macierz[v-1][i] == 1 && macierz[i-1][v-1] == 1){
				st_in++;
				st_out++;
				continue;
			}
			if(macierz[v-1][i] == 1){
				st_out++;
			}
			if(macierz[v-1][i] == -1){
				st_in++;
			}
		}
		std::cout << "Stopień in: " << st_in << " | Stopień out: " << st_out << "\n";
	}
	void Graph_MS::wypisz(){
		std::cout << "Macierz sąsiedztwa: \n";
		for(int i = 0; i < V; i++){
			for(int j = 0; j < V; j++){
				std::cout << std::setw(2) << macierz[i][j] << " ";
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

	//macierz incydencji
	Graph_MI::Graph_MI(int v, int e){
		V = v;
		E = e;
		obecny = 0;
		macierz = new int*[E];
		for(int i = 0; i < E; i++){
			macierz[i] = new int[V];
			for(int j = 0; j < V; j++){
				macierz[i][j] = 0;
			}
		}
	}
	int Graph_MI::istnieje(int x, int y){
		for(int i = 0; i < E; i++){
			if(macierz[i][x-1] == 2) return i;
			if((macierz[i][x-1] == -1 && macierz[i][y-1] == 1)||(macierz[i][x-1] == 1 && macierz[i][y-1] == -1))return i;
		}
		return -1;
	}
	void Graph_MI::dodaj_luk(int x, int y){
		int e = istnieje(x,y);
		if(e != -1){
			std::cout << "Łuk " << x << " " << y <<" istnieje!\n";
			return;
		}else{
			if(x == y){
				macierz[obecny][x-1] = 2;
				obecny++;
				return;
			}
			macierz[obecny][x-1] = 1;
			macierz[obecny][y-1] = -1;
		}
		obecny++;
	}
	void Graph_MI::usun_luk(int x, int y){
		int e = istnieje(x,y);
		if(e != -1){
			delete macierz[e];
			for(int i = e; i < obecny-1; i++){
				macierz[i] = macierz[i+1];
			}
			macierz[obecny-1] = new int[V];
			if(oceny==E)
				for(int i = 0; i < V; i++){
					macierz[obecny-1][i] = 0;
				}
			obecny--;
		}else{
			std::cout << "Łuk nie istnieje!\n";
			return;
		}
	}
	void Graph_MI::nastepniki(int v){
		std::cout << "Lista nastepników: " << v;
		for(int i = 0; i < E; i++){
			if(macierz[i][v-1] == 1){
				for(int j = 0; j < V; j++){
					if(macierz[i][j] == -1){
						std::cout  << " -> " << j+1;
					}
				}
			}
			if(macierz[i][v-1] == 2){
				std::cout  << " -> " << v;
			}
		}
		std::cout << "\n";
	}
	void Graph_MI::poprzedniki(int v){
		std::cout << "Lista poprzedników: " << v;
		for(int i = 0; i < E; i++){
			if(macierz[i][v-1] == -1){
				for(int j = 0; j < V; j++){
					if(macierz[i][j] == 1){
						std::cout  << " -> " << j+1;
					}
				}
			}
			if(macierz[i][v-1] == 2){
				std::cout  << " -> " << v;
			}
		}
		std::cout << "\n";
	}
	void Graph_MI::stopien(int v){
		int st_in = 0, st_out = 0;
		for(int i = 0; i < E; i++){
			if(macierz[i][v-1] == 2){
				st_in++;
				st_out++;
				continue;
			}
			if(macierz[i][v-1] == 1){
				st_out++;
			}
			if(macierz[i][v-1] == -1){
				st_in++;
			}
		}
		std::cout << "Stopień in: " << st_in << " | Stopień out: " << st_out << "\n";
	}
	void Graph_MI::wypisz(){
		std::cout << "Macierz incydencji: \n";
		for(int i = 0; i < V; i++){
			for(int j = 0; j < E; j++){
				std::cout << std::setw(2) << macierz[j][i] << " ";
			}
			std::cout << std::endl;
		std::cout << std::endl;
		}
	}
	Graph_MI::~Graph_MI(){
		for(int i = 0; i < E; i++){
			delete[] macierz[i];
		}
		delete [] macierz;
	}
	//lista nastepnikow
	Graph_LN::Graph_LN(int v, int e){
		V = v;
		E = e;
		lista = new Lista[V];
		for(int i = 0; i < V; i++){
			lista[i].key = i+1;
			lista[i].next = NULL;
			lista[i].prev = NULL;
		}
	}
	bool Graph_LN::istnieje(int x, int y){
		Lista *temp = &lista[x-1];
		while(temp -> next != NULL){
			temp = temp->next;
			if (temp->key == y) return true;
		}
		return false;
	}
	void Graph_LN::dodaj_luk(int x, int y){
		if(istnieje(x,y)){
			std::cout << "Łuk " << x << " " << y <<" istnieje!\n";
			return;
		}else{
			Lista *temp = &lista[x-1];
			while(temp -> next != NULL){
				temp = temp -> next;
				if(temp -> key > y){
					temp = temp -> prev;
					break;
				}
			}
			Lista * dod = new Lista;
			if(temp -> next != NULL){
				(temp->next)->prev = dod;
			}
			dod -> key = y;
			dod -> next = temp -> next;
			dod -> prev = temp;
			temp -> next = dod;
		}
	}
	void Graph_LN::usun_luk(int x, int y){
		Lista *temp = &lista[x-1];
		while(temp -> next != NULL){
			temp = temp -> next;
			if(temp -> key == y){
				if(temp -> prev != NULL){
					(temp -> prev) -> next = temp -> next;
				}
				if(temp -> next != NULL){
					(temp->next)->prev = temp -> prev;
				}
				delete temp;
				return;
			}
		}
		std::cout << "Łuk nie istnieje!\n";
	}
	void Graph_LN::nastepniki(int v){
		std::cout << "Lista następników " << v <<": \n";
		std::cout << lista[v-1].key;
		Lista *temp = &lista[v-1];
		while(temp -> next != NULL){
			temp = temp->next;
			std::cout << " -> " << temp->key;
		}
		std::cout << std::endl;
	}
	void Graph_LN::poprzedniki(int v){
		std::cout << "Lista poprzedników " << v <<": \n";
		std::cout << lista[v-1].key;
		Lista *temp;
		for(int i = 0; i < V; i++){
			temp = &lista[i];
			while(temp -> next != NULL){
				temp = temp->next;
				if(temp -> key == v){
					std::cout << " -> " << i+1;
					break;
				}
			}
		}
		std::cout << std::endl;
	}
	void Graph_LN::stopien(int v){
		int st_in = 0, st_out = 0;
		Lista *temp = &lista[v-1];
		while(temp -> next != NULL){
			temp = temp->next;
			st_out++;
		}
		for(int i = 0; i < V; i++){
			temp = &lista[i];
			while(temp -> next != NULL){
				temp = temp->next;
				if(temp -> key == v){
					st_in++;
					break;
				}
			}
		}
		std::cout << "Stopień in: " << st_in << " | Stopień out: " << st_out << "\n";
	}
	void Graph_LN::wypisz(){
		std::cout << "Listy następników: \n";
		for(int i = 0; i < V; i++){
			std::cout << lista[i].key;
			Lista *temp = &lista[i];
			while(temp -> next != NULL){
				temp = temp->next;
				std::cout << " -> " << temp->key;
			}
			std::cout << std::endl;
		}
	}
	Graph_LN::~Graph_LN(){
		Lista *temp;
		for(int i = 0; i < V; i++){
			temp = &lista[i];
			while(temp -> next != NULL){
				temp = temp -> next;
			}
			while(temp != &lista[i]){
				temp = temp -> prev;
				delete temp->next;
			}
		}
		delete[] lista;
	}
	//lista poprzednikow
	Graph_LP::Graph_LP(int v, int e){
		V = v;
		E = e;
		lista = new Lista[V];
		for(int i = 0; i < V; i++){
			lista[i].key = i+1;
			lista[i].next = NULL;
			lista[i].prev = NULL;
		}
	}
	bool Graph_LP::istnieje(int y, int x){
		Lista *temp = &lista[x-1];
		while(temp -> next != NULL){
			temp = temp->next;
			if (temp->key == y) return true;
		}
		return false;
	}
	void Graph_LP::dodaj_luk(int y, int x){
		if(istnieje(x,y)){
			std::cout << "Łuk " << x << " " << y <<" istnieje!\n";
			return;
		}else{
			Lista *temp = &lista[x-1];
			while(temp -> next != NULL){
				temp = temp -> next;
				if(temp -> key > y){
					temp = temp -> prev;
					break;
				}
			}
			Lista * dod = new Lista;
			if(temp -> next != NULL){
				(temp->next)->prev = dod;
			}
			dod -> key = y;
			dod -> next = temp -> next;
			dod -> prev = temp;
			temp -> next = dod;
		}
	}
	void Graph_LP::usun_luk(int y, int x){
		Lista *temp = &lista[x-1];
		while(temp -> next != NULL){
			temp = temp -> next;
			if(temp -> key == y){
				if(temp -> prev != NULL){
					(temp -> prev) -> next = temp -> next;
				}
				if(temp -> next != NULL){
					(temp->next)->prev = temp -> prev;
				}
				delete temp;
				return;
			}
		}
		std::cout << "Łuk nie istnieje!\n";
	}
	void Graph_LP::poprzedniki(int v){
		std::cout << "Lista poprzedników " << v <<": \n";
		std::cout << lista[v-1].key;
		Lista *temp = &lista[v-1];
		while(temp -> next != NULL){
			temp = temp->next;
			std::cout << " -> " << temp->key;
		}
		std::cout << std::endl;
	}
	void Graph_LP::nastepniki(int v){
		std::cout << "Lista następników " << v <<": \n";
		std::cout << lista[v-1].key;
		Lista *temp;
		for(int i = 0; i < V; i++){
			temp = &lista[i];
			while(temp -> next != NULL){
				temp = temp->next;
				if(temp -> key == v){
					std::cout << " -> " << i+1;
					break;
				}
			}
		}
		std::cout << std::endl;
	}
	void Graph_LP::stopien(int v){
		int st_in = 0, st_out = 0;
		Lista *temp = &lista[v-1];
		while(temp -> next != NULL){
			temp = temp->next;
			st_in++;
		}
		for(int i = 0; i < V; i++){
			temp = &lista[i];
			while(temp -> next != NULL){
				temp = temp->next;
				if(temp -> key == v){
					st_out++;
					break;
				}
			}
		}
		std::cout << "Stopień in: " << st_in << " | Stopień out: " << st_out << "\n";
	}
	void Graph_LP::wypisz(){
		std::cout << "Listy poprzedników: \n";
		for(int i = 0; i < V; i++){
			std::cout << lista[i].key;
			Lista *temp = &lista[i];
			while(temp -> next != NULL){
				temp = temp->next;
				std::cout << " -> " << temp->key;
			}
			std::cout << std::endl;
		}
	}
	Graph_LP::~Graph_LP(){
		Lista *temp;
		for(int i = 0; i < V; i++){
			temp = &lista[i];
			while(temp -> next != NULL){
				temp = temp -> next;
			}
			while(temp != &lista[i]){
				temp = temp -> prev;
				delete temp->next;
			}
		}
		delete[] lista;
	}
	//klasa topologicznego
	Graph::Graph(int v, int e){
		std::cout << "Proszę podać dane, obowiązujący format: WIERZCHOŁEK WIERZCHOŁEK, oznaczające łuk w grafie: \n";
		kolor = new short[v];
		topologicznie = new int[v];
		miejsce = v-1;
		V = v;
		E = e;
		//przygotowanie struktur danych
		m_sasiedztwa = new int*[v];
		for(int i = 0; i < V; i++){
			m_sasiedztwa[i] = new int[v];
			for(int j = 0; j < V; j++){
				m_sasiedztwa[i][j] = 0;
			}
		}
			m_incydencji = new int*[v];
			for(int i = 0; i < V; i++){
				m_incydencji[i] = new int[E];
			for(int j = 0; j < E; j++){
				m_incydencji[i][j] = 0;
			}
		}
		l_nastepnikow = new Lista[V];
		for(int i = 0; i < V; i++){
			l_nastepnikow[i].key = i+1;
			l_nastepnikow[i].next = NULL;
			l_nastepnikow[i].prev = NULL;
		}
		l_poprzednikow = new Lista[V];
		for(int i = 0; i < V; i++){
			l_poprzednikow[i].key = i+1;
			l_poprzednikow[i].next = NULL;
			l_poprzednikow[i].prev = NULL;
		}
		//koniec przygotowania struktur danych
		//wczytywanie do nich danych
		int x,y;
		while(e){
			std::cin >> x >> y;
			//listy
			//nastepniki
			Lista *temp;
			temp = &l_nastepnikow[x-1];
			while(temp -> next != NULL){
				temp = temp -> next;
				if(temp -> key > y){
						temp = temp -> prev;
					break;
				}
			}
			Lista * dod = new Lista;
			if(temp -> next != NULL){
				(temp->next)->prev = dod;
			}
			dod -> key = y;
			dod -> next = temp -> next;
			dod -> prev = temp;
			temp -> next = dod;
			//poprzedniki
			temp = new Lista;
			temp = &l_poprzednikow[y-1];
			while(temp -> next != NULL){
				temp = temp -> next;
				if(temp -> key > x){
					temp = temp -> prev;
					break;
				}
			}
			dod = new Lista;
			if(temp -> next != NULL){
				(temp->next)->prev = dod;
			}
			dod -> key = x;
			dod -> next = temp -> next;
			dod -> prev = temp;
			temp -> next = dod;
			//macierze
			m_sasiedztwa[x-1][y-1] = 1;
			if (m_sasiedztwa[y-1][x-1] != 1) m_sasiedztwa[y-1][x-1] = -1;
			//krawedzie sa podawane w kolejnosci w jakiej sa numerowane
			if (x==y){
				m_incydencji[x-1][E-e] = 2; 
				e--;
				continue;
			}
			m_incydencji[x-1][E-e] = -1; 
			m_incydencji[y-1][E-e] = 1;
			e--;
		}
	}
	void Graph::znajdz_bialy(int v){
		Lista *temp = &l_nastepnikow[v-1], *temp2;
		while(temp -> next != NULL){
			temp = temp -> next;
			if(kolor[temp->key - 1] != 0) continue;
			else{
				kolor[temp->key - 1] = 1;
				znajdz_bialy(temp->key);
			}
		}
		if(kolor[temp->key - 1] == 2){
			temp = &l_nastepnikow[v-1];
		}
		if(kolor[temp->key - 1] != 0){
			kolor[temp->key - 1] = 2;
			topologicznie[miejsce--] = temp->key;
		}
	}
	void Graph::sort_topologiczne(){
		bool flag = true;
		//0 - bialy, 1 - szary, 2 - czarny
		int wierzcholek, ktory = 0;
		Lista *temp;
		temp = l_poprzednikow;
		for(int i = 0; i < V; i++){
			if(temp[i].next == NULL){
				if (kolor[i] != 0) continue;
				temp = &temp[i];
				break;
			}
			flag = false;
		}
		if(flag == false){
			std::cout << "Nie istnieje kolejność topologiczna!\n";
			return;
		}
		wierzcholek = temp->key;
		kolor[wierzcholek - 1] = 1;
		temp = &l_nastepnikow[wierzcholek-1];
		znajdz_bialy(wierzcholek);
		if (miejsce != -1){
			sort_topologiczne();
		}else{
			std::cout << "Wierzchołki grafu posortowane topologicznie: \n";
			for(int i = 0; i < V; i++){
				std::cout << topologicznie[i] << " ";
			}
			std::cout << std::endl;
		}
	}
	void Graph::wypisz_macierz(){
		std::cout << "Macierz sąsiedztwa: \n";
		for(int i = 0; i < V; i++){
			for(int j = 0; j < V; j++){
				std::cout << std::setw(2) << m_sasiedztwa[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Macierz incydencji: \n";
		for(int i = 0; i < V; i++){
			for(int j = 0; j < E; j++){
				std::cout << std::setw(2) << m_incydencji[i][j] << " ";
			}
				std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	void Graph::wypisz_listy(){
		std::cout << "Listy następników: \n";
		for(int i = 0; i < V; i++){
			std::cout << l_nastepnikow[i].key;
			Lista *temp = &l_nastepnikow[i];
			while(temp -> next != NULL){
				temp = temp->next;
				std::cout << " -> " << temp->key;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Listy poprzedników: \n";
		for(int i = 0; i < V; i++){
			std::cout << l_poprzednikow[i].key;
			Lista *temp = &l_poprzednikow[i];
			while(temp -> next != NULL){
				temp = temp->next;
				std::cout << " -> " << temp->key;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	Graph::~Graph(){
		for(int i = 0; i < V; i++){
			delete[] m_sasiedztwa[i];
		}
		for(int i = 0; i < V; i++){
			delete[] m_incydencji[i];
		}
		Lista *temp;
		for(int i = 0; i < V; i++){
			temp = &l_nastepnikow[i];
			while(temp -> next != NULL){
				temp = temp -> next;
			}
			while(temp != &l_nastepnikow[i]){
				temp = temp -> prev;
				delete temp->next;
			}
		}
		for(int i = 0; i < V; i++){
			temp = &l_poprzednikow[i];
			while(temp -> next != NULL){
				temp = temp -> next;
			}
			while(temp != &l_poprzednikow[i]){
				temp = temp -> prev;
				delete temp->next;
			}
		}
		delete[] kolor;
		delete[] topologicznie;
		delete[] m_incydencji;
		delete[] m_sasiedztwa;
		delete[] l_nastepnikow;
		delete[] l_poprzednikow;
	}