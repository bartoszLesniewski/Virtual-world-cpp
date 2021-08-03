#include <iostream>
#include "Lis.h"
#include "Swiat.h"

Lis::Lis(Swiat& swiat, std::pair<int, int> polozenie) : Zwierze(swiat, "Lis", 3, 7, polozenie, 'L') { }

std::vector<std::pair<int, int>> Lis::wybierzBezpiecznePola() const
{
	std::vector<std::pair<int, int>> wolnePola = swiat.getSasiednieDowolnePola(polozenie);

	for (auto it = wolnePola.begin(); it != wolnePola.end();)
	{
		if (swiat.getOrganizmNaPlanszy(*it) != nullptr && swiat.getOrganizmNaPlanszy(*it)->getSila() > this->sila)
			it = wolnePola.erase(it);
		else
			++it;
	}

	return wolnePola;
}

void Lis::akcja(int zasiegRuchu)
{
	std::vector<std::pair<int, int>> wolnePola = wybierzBezpiecznePola();
	if (!wolnePola.empty())
	{
		int los = losujSposrodMozliwychPol(wolnePola);

		std::pair<int, int> nowePolozenie = wolnePola[los];

		if (swiat.czyZajetePole(nowePolozenie))
			swiat.getOrganizmNaPlanszy(nowePolozenie)->kolizja(this);

		else
		{
			swiat.aktualizujPolozenieNaPlanszy(polozenie, nowePolozenie);
			zmienPolozenie(nowePolozenie);
		}
	}
	//else
		//swiat.dodajKomunikat("Lis nie rusza sie z pola " + polozenieToString() + ", bo nie jest bezpiecznie");
}

