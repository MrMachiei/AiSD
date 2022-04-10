#include <iostream>
#include <ctime>
using namespace std;

class Plecak{
private:
	int **przedmioty, ladownosc, ile_p, **ladunek, masa, wartosc,**ubytek;
public:
	Plecak(int ile, int p_od, int p_do, int w_od, int w_do, int l_od, int l_do);
	~Plecak();
	void wypisz();
	void maksymalizuj();
	void wypiszMaks();
	void DUAL();
	void wypiszDUAL();
};















































//©M.J.W.2020