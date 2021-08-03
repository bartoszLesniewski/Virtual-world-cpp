#pragma once
#include <vector>
#include "Organizm.h"

class Czlowiek;

class Swiat
{
private:
	std::vector<Organizm*> organizmy;
	Organizm*** plansza;
	Czlowiek* czlowiek;
	int nrTury;
	int dlugoscPlanszy;
	int szerokoscPlanszy;
	std::vector<std::string> komunikaty;

	std::pair<int, int> losujPozycje() const;
	void dodajOrganizmy();
	void stworzPlansze();
	void wypelnijPlansze();
	void inicjujSwiat();
	void zapiszGre(bool& czyPoprawnyPrzycisk, bool& czyWyjsc);
	void wczytajGre();
	
	void wyswietlNaglowek() const;
	void wyswietlInstrukcje() const;
	void wybierzOpcje();
	void wyswietlKomunikatyDoSterowania();
	void wyswietlWszystko();
	bool sterowanie();
	void poruszanieCzlowiekiem(int akcja, bool& czyPoprawnyPrzycisk);
	void nadajKierunekCzlowiekowi(Kierunek kierunek, bool& czyPoprawnyPrzycisk);
	void wczytajDane();
	void sortujOrganizmy();
	void wykonajTure();
	void rysujSwiat() const;
	void wyswietlKomunikaty();
	void aktualizujWiekOrganizmow();
	void symulacja();

public:
	Swiat();
	~Swiat();
	void menu();
	int getDlugoscPlanszy() const;
	int getSzerokoscPlanszy() const;
	bool czyZajetePole(std::pair<int, int> pozycja) const;
	Organizm* getOrganizmNaPlanszy(std::pair<int, int> pozycja) const;
	void aktualizujPolozenieNaPlanszy(std::pair<int, int> poprzedniePolozenie, std::pair<int, int> nowePolozenie);
	void zamienOrganizmyNaPlanszy(std::pair<int, int> polozenie1, std::pair<int, int> polozenie2);
	void usunOrganizmZPlanszy(std::pair<int, int> polozenie);
	void dodajKomunikat(std::string);
	std::vector<std::pair<int, int>> getSasiednieWolnePola(std::pair<int, int> polozenie) const;
	std::vector<std::pair<int, int>> getSasiednieDowolnePola(std::pair<int, int> polozenie) const;
	void stworzOrganizm(std::string gatunek, std::pair<int, int> polozenie);
};