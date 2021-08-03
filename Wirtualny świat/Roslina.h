#pragma once
#include "Organizm.h"

class Roslina : public Organizm
{
protected:
	Roslina(Swiat& swiat, std::string gatunek, int sila, std::pair<int, int> polozenie, char znak);
public:
	virtual ~Roslina() = 0;
	void akcja(int zasiegRuchu = 1) override;
	void kolizja(Organizm* atakujacy) override;
};