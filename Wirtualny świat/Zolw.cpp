#include "Zolw.h"
#include "Swiat.h"

Zolw::Zolw(Swiat& swiat, std::pair<int, int> polozenie) : Zwierze(swiat, "Zolw", 2, 1, polozenie, 'Z') { }

void Zolw::akcja(int zasiegRuchu)
{
	int los = rand() % 100 + 1;

	if (los <= 25)
		Zwierze::akcja();
	//else
		//swiat.dodajKomunikat(getGatunek() + " " + polozenieToString() + " nie zmienia swojej pozycji");
}

bool Zolw::czyOdbilAtak(Organizm* atakujacy)
{
	if (atakujacy->getSila() < 5)
	{
		swiat.dodajKomunikat(getGatunek() + polozenieToString() + " odpiera atak " + atakujacy->getGatunek() + " " + atakujacy->polozenieToString());

		return true;
	}

	return false;
}