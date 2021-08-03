#pragma once
#include "Zwierze.h"

class Antylopa : public Zwierze
{
public:
	Antylopa(Swiat& swiat, std::pair<int, int> polozenie);
	void akcja(int zasiegRuchu = 1) override;
	bool czyOdbilAtak(Organizm* atakujacy) override;
};