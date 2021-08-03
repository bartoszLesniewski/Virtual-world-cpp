#include "Antylopa.h"
#include "Swiat.h"

Antylopa::Antylopa(Swiat& swiat, std::pair<int, int> polozenie) : Zwierze(swiat, "Antylopa", 4, 4, polozenie, 'A') { }

void Antylopa::akcja(int zasiegRuchu)
{
	int zasieg = rand() % 2 + 1;
	Zwierze::akcja(zasieg);
}

bool Antylopa::czyOdbilAtak(Organizm* atakujacy)
{
	int szansa = rand() % 100 + 1;

	if (szansa <= 50)
	{
		std::string komunikat = getGatunek() + " " + polozenieToString() + " ucieka przed walka na pole ";

		std::pair<int, int> polozenieAtakujacego = atakujacy->getPolozenie();
		std::vector<std::pair<int, int>> wolneMiejsca = swiat.getSasiednieWolnePola(polozenie);
		wolneMiejsca.push_back(polozenieAtakujacego);
		int los = losujSposrodMozliwychPol(wolneMiejsca);

		if (wolneMiejsca[los] == polozenieAtakujacego)
			swiat.zamienOrganizmyNaPlanszy(polozenie, polozenieAtakujacego);
			
		else
		{
			swiat.aktualizujPolozenieNaPlanszy(polozenie, wolneMiejsca[los]);
			swiat.aktualizujPolozenieNaPlanszy(polozenieAtakujacego, polozenie);
		}

		atakujacy->zmienPolozenie(polozenie);
		polozenie = wolneMiejsca[los];

		komunikat += polozenieToString();
		swiat.dodajKomunikat(komunikat);

		return true;
	}

	return false;
}