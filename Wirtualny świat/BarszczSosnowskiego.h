#pragma once
#include "Roslina.h"

class BarszczSosnowskiego : public Roslina
{
public:
	BarszczSosnowskiego(Swiat& swiat, std::pair<int, int> polozenie);
	void akcja(int zasiegRuchu = 1) override;
	void kolizja(Organizm* atakujacy) override;
};