#include "Roslina.h"
#include "Swiat.h"

Roslina::Roslina(Swiat& swiat, std::string gatunek, int sila, std::pair<int, int> polozenie, char znak) : Organizm(swiat, gatunek, sila, 0, polozenie, znak) { }

void Roslina::akcja(int zasiegRuchu)
{
	int szansa = rand() % 100 + 1;

	if (szansa <= 10)
	{
		std::vector<std::pair<int, int>> wolnePola = swiat.getSasiednieWolnePola(polozenie);

		if (!wolnePola.empty())
		{
			int los = losujSposrodMozliwychPol(wolnePola);
			swiat.stworzOrganizm(gatunek, wolnePola[los]);
		}
	}
}

void Roslina::kolizja(Organizm* atakujacy)
{
	swiat.dodajKomunikat(atakujacy->getGatunek() + " " + atakujacy->polozenieToString() + " zjada " + gatunek + " " + polozenieToString());
	this->zabij();
	swiat.aktualizujPolozenieNaPlanszy(atakujacy->getPolozenie(), this->getPolozenie());
	atakujacy->zmienPolozenie(this->getPolozenie());
}

Roslina::~Roslina()
{

}