#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Kierunek.h"

class Swiat;

class Organizm
{
protected:
	Swiat& swiat;
	int sila;
	int inicjatywa;
	std::pair<int, int> polozenie;
	char znak;
	bool czyZyje;
	int wiek;
	std::string gatunek;
	Organizm(Swiat& swiat, std::string gatunek, int sila, int inicjatywa, std::pair<int, int> polozenie, char znak, bool czyZyje = true, int wiek = 0);
	Kierunek losujKierunek() const;
	std::pair<int, int> ustalNowePolozenie(Kierunek kierunek, int zasiegRuchu) const;
	int losujSposrodMozliwychPol(std::vector<std::pair<int, int>> wolnePola) const;
public:
	virtual void akcja(int zasiegRuchu = 1) = 0;
	virtual void kolizja(Organizm* atakujacy) = 0;
	virtual void rysowanie() const;
	virtual ~Organizm();
	bool czyMozliwyRuch(Kierunek kierunek, int zasiegRuchu) const;
	int getSila() const;
	void setSila(int wartosc);
	int getInicjatywa() const;
	std::pair<int, int> getPolozenie() const;
	int getWiek() const;
	void setWiek(int nowyWiek);
	std::string getGatunek() const;
	bool sprawdzCzyZyje() const;
	std::string polozenieToString() const;
	void zmienPolozenie(std::pair<int, int> nowePolozenie);
	void zabij();
};