#include "BarszczSosnowskiego.h"
#include "Swiat.h"
#include "Zwierze.h"

BarszczSosnowskiego::BarszczSosnowskiego(Swiat& swiat, std::pair<int, int> polozenie) : Roslina(swiat, "Barszcz Sosnowskiego", 10, polozenie, 'B') { };

void BarszczSosnowskiego::akcja(int zasiegRuchu)
{
	std::vector<std::pair<int, int>> wolnePola = swiat.getSasiednieDowolnePola(polozenie);

	for (auto it = wolnePola.begin(); it != wolnePola.end(); ++it)
	{
		Organizm* tmp = swiat.getOrganizmNaPlanszy(*it);
		if (tmp != nullptr && dynamic_cast<Zwierze*>(tmp) != nullptr)
		{
			swiat.dodajKomunikat(gatunek + " " + polozenieToString() + " zabija " + tmp->getGatunek() + " " + tmp->polozenieToString());
			tmp->zabij();
		}
	}
}

void BarszczSosnowskiego::kolizja(Organizm* atakujacy)
{
	swiat.dodajKomunikat(atakujacy->getGatunek() + " " + atakujacy->polozenieToString() + " ginie w wyniku zjedzenia " + getGatunek() + " " + polozenieToString());
	atakujacy->zabij();
	this->zabij();
}