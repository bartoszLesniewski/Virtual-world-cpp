#pragma once
#include "Zwierze.h"

class Zolw : public Zwierze
{
public:
	Zolw (Swiat& swiat, std::pair<int, int> polozenie);
	void akcja(int zasiegRuchu = 1) override;
	bool czyOdbilAtak(Organizm* atakujacy) override;
};