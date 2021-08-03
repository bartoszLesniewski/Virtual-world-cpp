#pragma once
#include "Zwierze.h"

class Lis : public Zwierze
{
private:
	std::vector<std::pair<int, int>> wybierzBezpiecznePola() const;
public:
	Lis(Swiat& swiat, std::pair<int, int> polozenie);
	void akcja(int zasiegRuchu = 1) override;
};