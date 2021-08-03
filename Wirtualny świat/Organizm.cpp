#include <iostream>
#include "Organizm.h"
#include "Swiat.h"

Organizm::Organizm(Swiat& swiat, std::string gatunek, int sila, int inicjatywa, std::pair<int, int> polozenie, char znak, bool czyZyje, int wiek) : swiat(swiat), gatunek(gatunek), sila(sila), inicjatywa(inicjatywa), polozenie(polozenie), znak(znak), czyZyje(czyZyje), wiek(wiek) { }

Organizm::~Organizm()
{

}

void Organizm::rysowanie() const
{
	std::cout << znak;
}

int Organizm::getSila() const
{
	return sila;
}

void Organizm::setSila(int wartosc)
{
	sila = wartosc;
}

int Organizm::getInicjatywa() const
{
	return inicjatywa;
}

std::pair<int, int> Organizm::getPolozenie() const
{
	return polozenie;
}

int Organizm::getWiek() const
{
	return wiek;
}

void Organizm::setWiek(int nowyWiek)
{
	wiek = nowyWiek;
}

std::string Organizm::getGatunek() const
{
	return gatunek;
}

bool Organizm::sprawdzCzyZyje() const
{
	return czyZyje;
}

void Organizm::zabij()
{
	czyZyje = false;
	swiat.usunOrganizmZPlanszy(getPolozenie());
}

std::string Organizm::polozenieToString() const
{
	std::string polozenieString = "(" + std::to_string(polozenie.first) + ", " + std::to_string(polozenie.second) + ")";

	return polozenieString;
}

bool Organizm::czyMozliwyRuch(Kierunek kierunek, int zasiegRuchu) const
{
	std::pair<int, int> tmpPolozenie = polozenie;

	if (kierunek == Kierunek::LEWO)
		tmpPolozenie.first -= zasiegRuchu;
	else if (kierunek == Kierunek::PRAWO)
		tmpPolozenie.first += zasiegRuchu;
	else if (kierunek == Kierunek::GORA)
		tmpPolozenie.second -= zasiegRuchu;
	else if (kierunek == Kierunek::DOL)
		tmpPolozenie.second += zasiegRuchu;

	if (tmpPolozenie.first < 0 || tmpPolozenie.first >= swiat.getDlugoscPlanszy())
		return false;

	if (tmpPolozenie.second < 0 || tmpPolozenie.second >= swiat.getSzerokoscPlanszy())
		return false;

	return true;
}

std::pair<int, int> Organizm::ustalNowePolozenie(Kierunek kierunek, int zasiegRuchu) const
{
	std::pair<int, int> nowePolozenie = polozenie;

	if (kierunek == Kierunek::LEWO)
		nowePolozenie.first -= zasiegRuchu;
	else if (kierunek == Kierunek::PRAWO)
		nowePolozenie.first += zasiegRuchu;
	else if (kierunek == Kierunek::GORA)
		nowePolozenie.second -= zasiegRuchu;
	else if (kierunek == Kierunek::DOL)
		nowePolozenie.second += zasiegRuchu;

	return nowePolozenie;
}

Kierunek Organizm::losujKierunek() const
{
	int x = rand() % 4;

	return static_cast<Kierunek>(x);
}

void Organizm::zmienPolozenie(std::pair<int, int> nowePolozenie)
{
	//std::string komunikat = getGatunek() + " " + polozenieToString() + " zmienia swoje polozenie na ";

	polozenie = nowePolozenie;

	//komunikat += polozenieToString();
	//swiat.dodajKomunikat(komunikat);
}

int Organizm::losujSposrodMozliwychPol(std::vector<std::pair<int, int>> wolnePola) const
{
	int los;
	if (wolnePola.size() > 1)
		los = rand() % (wolnePola.size());
	else
		los = 0;

	return los;
}


