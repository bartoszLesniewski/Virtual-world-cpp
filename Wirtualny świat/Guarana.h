#pragma once
#include "Roslina.h"

class Guarana : public Roslina
{
public:
	Guarana(Swiat& swiat, std::pair<int, int> polozenie);
	void kolizja(Organizm* atakujacy) override;
};