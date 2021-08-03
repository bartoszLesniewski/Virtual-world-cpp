#include "Zwierze.h"
#include "Swiat.h"
#include <iostream>

Zwierze::Zwierze(Swiat& swiat, std::string gatunek, int sila, int inicjatywa, std::pair<int, int> polozenie, char znak) : Organizm(swiat, gatunek, sila, inicjatywa, polozenie, znak) { }

void Zwierze::akcja(int zasiegRuchu)
{
	std::pair<int, int> nowePolozenie, poprzedniaPozycja;
	Kierunek kierunek;
	do
	{
		kierunek = losujKierunek();

	} while (!czyMozliwyRuch(kierunek, zasiegRuchu));

	nowePolozenie = ustalNowePolozenie(kierunek, zasiegRuchu);
	
	if (swiat.czyZajetePole(nowePolozenie))
		swiat.getOrganizmNaPlanszy(nowePolozenie)->kolizja(this);
	
	else
	{
		swiat.aktualizujPolozenieNaPlanszy(polozenie, nowePolozenie);
		zmienPolozenie(nowePolozenie);
	}
}

bool Zwierze::czyOdbilAtak(Organizm* atakujacy)
{
	if (sila <= atakujacy->getSila())
		return false;

	swiat.dodajKomunikat(atakujacy->getGatunek() + " " + atakujacy->polozenieToString() + " ginie podczas ataku na " + getGatunek() + " " + polozenieToString());

	atakujacy->zabij();

	return true;
}

void Zwierze::kolizja(Organizm* atakujacy)
{
	if (gatunek == atakujacy->getGatunek())
	{
		if (this->wiek > 0)
			rozmnazanie(atakujacy);
		else
			swiat.dodajKomunikat("Nieudana proba rozmnazania organizmu: " + atakujacy->getGatunek() + " " + atakujacy->polozenieToString() + " z " + getGatunek() + " " + polozenieToString());
	}
	else if (!czyOdbilAtak(atakujacy))
	{
		swiat.dodajKomunikat(getGatunek() + " " + polozenieToString() + " ginie w wyniku ataku " + atakujacy->getGatunek() + " " + atakujacy->polozenieToString());

		this->zabij();
		swiat.aktualizujPolozenieNaPlanszy(atakujacy->getPolozenie(), this->getPolozenie());
		atakujacy->zmienPolozenie(this->getPolozenie());
	}
}

void Zwierze::rozmnazanie(Organizm* rodzic)
{
	std::vector<std::pair<int, int>> wolnePola = swiat.getSasiednieWolnePola(polozenie);
	std::vector<std::pair<int, int>> wolnePolaRodzic = swiat.getSasiednieWolnePola(rodzic->getPolozenie());

	wolnePola.insert(wolnePola.end(), wolnePolaRodzic.begin(), wolnePolaRodzic.end());

	if (wolnePola.empty())
		swiat.dodajKomunikat("Nieudana proba rozmnozenia " + rodzic->getGatunek() + " " + rodzic->polozenieToString() + " z " + getGatunek() + " " + polozenieToString() + " - brak miejsca");
	else
	{
		int los = losujSposrodMozliwychPol(wolnePola);
		swiat.stworzOrganizm(getGatunek(), wolnePola[los]);
	}
}

Zwierze::~Zwierze()
{

}