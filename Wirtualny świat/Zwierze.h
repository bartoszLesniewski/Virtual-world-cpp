#pragma once
#include "Organizm.h"

class Zwierze : public Organizm
{
protected:
	Zwierze(Swiat& swiat, std::string gatunek, int sila, int inicjatywa, std::pair<int, int> polozenie, char znak);
public:
	void akcja(int zasiegRuchu = 1) override;
	void kolizja(Organizm* atakujacy) override;
	virtual void rozmnazanie(Organizm* rodzic);
	virtual bool czyOdbilAtak(Organizm* atakujacy);
	virtual ~Zwierze() = 0;
};