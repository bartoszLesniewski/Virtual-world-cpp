#pragma once
#include "Roslina.h"

class WilczeJagody : public Roslina
{
public:
	WilczeJagody(Swiat& swiat, std::pair<int, int> polozenie);
	void kolizja(Organizm* atakujacy) override;
};