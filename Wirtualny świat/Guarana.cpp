#include "Guarana.h"

Guarana::Guarana(Swiat& swiat, std::pair<int, int> polozenie) : Roslina(swiat, "Guarana", 0, polozenie, 'G') { };

void Guarana::kolizja(Organizm* atakujacy)
{
	Roslina::kolizja(atakujacy);
	atakujacy->setSila(atakujacy->getSila() + 3);
}