#include "Czlowiek.h"
#include "Swiat.h"

Czlowiek::Czlowiek(Swiat& swiat, std::pair<int, int> polozenie) : Zwierze(swiat, "Czlowiek", 5, 4, polozenie, 'C')
{ 
	kierunekRuchu = Kierunek::NIEZDEFINIOWANY;
	tarczaAlzura = false;
	czasTrwaniaUmiejetnosciSpecjalnej = 0;  
};

void Czlowiek::setKierunekRuchu(Kierunek kierunek)
{
	kierunekRuchu = kierunek;
}

void Czlowiek::aktywujTarczeAlzura()
{
	tarczaAlzura = true;
}

void Czlowiek::dezaktywujTarczeAlzura()
{
	tarczaAlzura = false;
}

bool Czlowiek::czyAktywnaTarczaAlzura()
{
	return tarczaAlzura;
}

int Czlowiek::getCzasTrwaniaUmiejetnosciSpecjalnej()
{
	return czasTrwaniaUmiejetnosciSpecjalnej;
}

void Czlowiek::setCzasTrwaniaUmiejetnosciSpecjalnej(int wartosc)
{
	czasTrwaniaUmiejetnosciSpecjalnej = wartosc;
}

void Czlowiek::akcja(int zasiegRuchu)
{
	if (kierunekRuchu != Kierunek::NIEZDEFINIOWANY)
	{
		std::pair<int, int> nowePolozenie = ustalNowePolozenie(kierunekRuchu, zasiegRuchu);

		if (swiat.czyZajetePole(nowePolozenie))
			swiat.getOrganizmNaPlanszy(nowePolozenie)->kolizja(this);

		else
		{
			swiat.aktualizujPolozenieNaPlanszy(polozenie, nowePolozenie);
			zmienPolozenie(nowePolozenie);
		}

		kierunekRuchu = Kierunek::NIEZDEFINIOWANY;
	}
}

bool Czlowiek::czyOdbilAtak(Organizm* atakujacy)
{
	if (tarczaAlzura)
	{
		std::vector<std::pair<int, int>> sasiedniePola = swiat.getSasiednieDowolnePola(polozenie);
		int los = losujSposrodMozliwychPol(sasiedniePola);

		swiat.dodajKomunikat(gatunek + " " + polozenieToString() + " odgania " + atakujacy->getGatunek() + " " + atakujacy->polozenieToString() + " na pozycje " + "(" + std::to_string(sasiedniePola[los].first) + ", " + std::to_string(sasiedniePola[los].second) + ")");

		if (!swiat.czyZajetePole(sasiedniePola[los]))
		{
			swiat.aktualizujPolozenieNaPlanszy(atakujacy->getPolozenie(), sasiedniePola[los]);
			atakujacy->zmienPolozenie(sasiedniePola[los]);
		}
		else if (sasiedniePola[los] != atakujacy->getPolozenie())
			swiat.getOrganizmNaPlanszy(sasiedniePola[los])->kolizja(atakujacy);

		return true;
	}
	
	bool wynikWalki = Zwierze::czyOdbilAtak(atakujacy);
	return wynikWalki;
}