#include "plecak.h"

Plecak::Plecak(int ile, int p_od, int p_do, int w_od, int w_do,int l_od, int l_do){
	ladownosc = rand() % (l_do - l_od + 1) +l_od;
	ile_p = ile;
	wartosc = 0;
	masa = 0;
	przedmioty = new int*[2];
	przedmioty[0] = new int[ile];
	przedmioty[1] = new int[ile];
	for(int i = 0; i < ile; i++){
		przedmioty[0][i] = rand() % (p_do - p_od + 1) +p_od;
		przedmioty[1][i] =rand() % (w_do - w_od + 1) +w_od;
	}
	for(int i = 0; i < ile_p; i++){
		wartosc += przedmioty[0][i];
		masa += przedmioty[1][i];
	}
	ladunek = new int*[ile_p+1];
	for(int i = 0; i <= ile_p; i++){
		ladunek[i] = new int[ladownosc+1];
	}
	for(int i = 0; i <= ladownosc; i++) ladunek[0][i] = 0;
	for(int i = 0; i <= ile_p; i++) ladunek[i][0] = 0;
	ubytek = new int*[ile_p+1];
	for(int i = 0; i <= ile_p; i++){
		ubytek[i] = new int[wartosc+1];
	}
	for(int i = 0; i <= wartosc; i++) ubytek[0][i] = 0;
	for(int i = 0; i <= ile_p; i++) ubytek[i][0] = 0;
}
Plecak::~Plecak(){
	for(int i = 0; i < ile_p; i++){
		delete[] ladunek[i];
	}
	for(int i = 0; i <= ile_p; i++){
		delete[] ubytek[i];
	}
	delete[] ubytek;
	delete[] przedmioty[0];
	delete[] przedmioty[1];
	delete[] przedmioty;
	delete[] ladunek;
}
void Plecak::DUAL(){
	for(int i = 1; i <= ile_p; i++){
		for(int j = 0; j <= wartosc; j++){
			if(przedmioty[0][i-1] > j) ubytek[i][j] = ubytek[i-1][j];
			else{
				if(ubytek[i-1][j] > (ubytek[i-1][j-przedmioty[0][i-1]]+przedmioty[1][i-1])) ubytek[i][j] = ubytek[i-1][j];
				else ubytek[i][j] = ubytek[i-1][j-przedmioty[0][i-1]]+przedmioty[1][i-1];
			}
		}
	}
}
void Plecak::wypiszDUAL(){
	int naj, wart = wartosc;
	for(int i = 0; i <= wartosc; i++){
		for(int j = 0; j <= ile_p; j++){
			if (masa - ubytek[j][i] <= ladownosc && i < wart){
				naj = masa-ubytek[j][i];
				wart = i;
			}
		}
	}
	cout << "Masa: " << naj << ", wartosc: " << wartosc-wart << endl;
}
void Plecak::wypisz(){
	cout << ile_p << endl;
	for(int i = 0; i <ile_p;i++){
		cout << przedmioty[0][i] << " " << przedmioty[1][i] << endl;
	}
	cout << ladownosc << endl;
}
void Plecak::maksymalizuj(){
	for(int i = 1; i <= ile_p; i++){
		for(int j = 0; j <= ladownosc; j++){
			if(przedmioty[1][i-1] > j) ladunek[i][j] = ladunek[i-1][j];
			else{
				if(ladunek[i-1][j] > (ladunek[i-1][j-przedmioty[1][i-1]]+przedmioty[0][i-1])) ladunek[i][j] = ladunek[i-1][j];
				else ladunek[i][j] = ladunek[i-1][j-przedmioty[1][i-1]]+przedmioty[0][i-1];
			}
		}
	}
}
void Plecak::wypiszMaks(){
	cout << "Maksymalna wartosc: " << ladunek[ile_p][ladownosc] << endl;
}























//©M.J.W.2020