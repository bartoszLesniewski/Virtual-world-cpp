#include "Mlecz.h"

Mlecz::Mlecz(Swiat& swiat, std::pair<int, int> polozenie) : Roslina(swiat, "Mlecz", 0, polozenie, 'M') { };

void Mlecz::akcja(int zasiegRuchu)
{
	for (int i = 1; i <= 3; i++)
		Roslina::akcja();
}
