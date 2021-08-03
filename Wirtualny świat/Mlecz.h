#pragma once
#include "Roslina.h"

class Mlecz : public Roslina
{
public:
	Mlecz(Swiat& swiat, std::pair<int, int> polozenie);
	void akcja(int zasiegRuchu = 1) override;
};