#include "WilczeJagody.h"
#include "Swiat.h"
#include "Zwierze.h"

WilczeJagody::WilczeJagody(Swiat& swiat, std::pair<int, int> polozenie) : Roslina(swiat, "Wilcze Jagody", 99, polozenie, 'J') { };

void WilczeJagody::kolizja(Organizm* atakujacy)
{
	if (dynamic_cast<Zwierze*>(atakujacy) != nullptr)
	{
		swiat.dodajKomunikat(atakujacy->getGatunek() + " " + atakujacy->polozenieToString() + " ginie w wyniku zjedzenia " + getGatunek() + " " + polozenieToString());
		atakujacy->zabij();
		this->zabij();
	}	
}