#pragma once
#include "Zwierze.h"

class Czlowiek : public Zwierze
{
private:
	Kierunek kierunekRuchu;
	bool tarczaAlzura;
	int czasTrwaniaUmiejetnosciSpecjalnej;
public:
	Czlowiek(Swiat& swiat, std::pair<int, int> polozenie);
	void akcja(int zasiegRuchu = 1) override;
	bool czyOdbilAtak(Organizm* atakujacy) override;
	void setKierunekRuchu(Kierunek kierunek);
	void aktywujTarczeAlzura();
	void dezaktywujTarczeAlzura();
	bool czyAktywnaTarczaAlzura();
	int getCzasTrwaniaUmiejetnosciSpecjalnej();
	void setCzasTrwaniaUmiejetnosciSpecjalnej(int wartosc);
};