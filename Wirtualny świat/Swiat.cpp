#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <algorithm>
#include <fstream>
#include "Swiat.h"
#include "Czlowiek.h"
#include "Kierunek.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"

#define STRZALKA_LEWO 75
#define STRZALKA_PRAWO 77
#define STRZALKA_GORA 72
#define STRZALKA_DOL 80
#define SPACJA 32

#define ILOSC_GATUNKOW_ZWIERZAT 5
#define ILOSC_GATUNKOW_ROSLIN 5
#define ZAPELNIENIE_SWIATA 0.9

Swiat::Swiat()
{
	dlugoscPlanszy = 0;
	szerokoscPlanszy = 0;
	nrTury = 0;
	plansza = nullptr;
	czlowiek = nullptr;
}

Swiat::~Swiat()
{
	for (auto it = organizmy.begin(); it != organizmy.end(); ++it)
		delete* it;
}

void Swiat::stworzPlansze()
{
	plansza = new Organizm * *[szerokoscPlanszy];

	for (int i = 0; i < szerokoscPlanszy; i++)
	{
		plansza[i] = new Organizm * [dlugoscPlanszy];

		for (int j = 0; j < dlugoscPlanszy; j++)
			plansza[i][j] = nullptr;
	}
}

std::pair<int, int> Swiat::losujPozycje() const
{
	bool powtorzona = false;
	int x, y;

	if (organizmy.size() < dlugoscPlanszy * szerokoscPlanszy) // jeœli jest jeszcze miejsce na planszy
	{
		do
		{
			x = rand() % dlugoscPlanszy;
			y = rand() % szerokoscPlanszy;


			for (auto it = organizmy.begin(); it != organizmy.end(); ++it)
			{
				std::pair<int, int> polozenie = (*it)->getPolozenie();

				if (polozenie.first == x && polozenie.second == y)
				{
					powtorzona = true;
					break;
				}
				else
					powtorzona = false;
			}
		} while (powtorzona == true);
	}
	else
		x = y = -1; 

	return std::make_pair(x, y);
}

void Swiat::dodajOrganizmy()
{
	czlowiek = new Czlowiek(*this, losujPozycje());
	organizmy.push_back(czlowiek);

	int iloscOrganizmowJednegoGatunku = (ZAPELNIENIE_SWIATA * (dlugoscPlanszy * szerokoscPlanszy)) / (ILOSC_GATUNKOW_ZWIERZAT + ILOSC_GATUNKOW_ROSLIN);
	bool nadmiar = false;
	
	if (iloscOrganizmowJednegoGatunku < 1 && dlugoscPlanszy * szerokoscPlanszy > 1)
	{
		iloscOrganizmowJednegoGatunku = 1;
		nadmiar = true;
	}

	for (int i = 0; i < iloscOrganizmowJednegoGatunku; i++)
	{
		organizmy.push_back(new Wilk(*this, losujPozycje()));
		organizmy.push_back(new Owca(*this, losujPozycje()));
		organizmy.push_back(new Lis(*this, losujPozycje()));
		organizmy.push_back(new Zolw(*this, losujPozycje()));
		organizmy.push_back(new Antylopa(*this, losujPozycje()));
		organizmy.push_back(new Trawa(*this, losujPozycje()));
		organizmy.push_back(new Mlecz(*this, losujPozycje()));
		organizmy.push_back(new Guarana(*this, losujPozycje()));
		organizmy.push_back(new WilczeJagody(*this, losujPozycje()));
		organizmy.push_back(new BarszczSosnowskiego(*this, losujPozycje()));
	}

	if (nadmiar)
	{
		for (auto it = organizmy.begin(); it != organizmy.end();)
		{
			if ((*it)->getPolozenie() == std::make_pair(-1, -1))
			{
				delete* it;
				it = organizmy.erase(it);
			}
			else
				++it;
		}
	}
}

void Swiat::wypelnijPlansze()
{
	for (auto it = organizmy.begin(); it != organizmy.end(); ++it)
	{
		std::pair<int, int> polozenie = (*it)->getPolozenie();
		plansza[polozenie.second][polozenie.first] = *it;
	}
}

void Swiat::stworzOrganizm(std::string gatunek, std::pair<int, int> polozenie)
{
	Organizm* nowyOrganizm;

	if (gatunek == "Wilk")
		nowyOrganizm = new Wilk(*this, polozenie);
	else if (gatunek == "Owca")
		nowyOrganizm = new Owca(*this, polozenie);
	else if (gatunek == "Lis")
		nowyOrganizm = new Lis(*this, polozenie);
	else if (gatunek == "Zolw")
		nowyOrganizm = new Zolw(*this, polozenie);
	else if (gatunek == "Antylopa")
		nowyOrganizm = new Antylopa(*this, polozenie);
	else if (gatunek == "Trawa")
		nowyOrganizm = new Trawa(*this, polozenie);
	else if (gatunek == "Mlecz")
		nowyOrganizm = new Mlecz(*this, polozenie);
	else if (gatunek == "Guarana")
		nowyOrganizm = new Guarana(*this, polozenie);
	else if (gatunek == "Wilcze Jagody")
		nowyOrganizm = new WilczeJagody(*this, polozenie);
	else if (gatunek == "Barszcz Sosnowskiego")
		nowyOrganizm = new BarszczSosnowskiego(*this, polozenie);
	else if (gatunek == "Czlowiek")
	{
		nowyOrganizm = new Czlowiek(*this, polozenie);
		czlowiek = dynamic_cast<Czlowiek*>(nowyOrganizm);
	}

	organizmy.push_back(nowyOrganizm);
	plansza[polozenie.second][polozenie.first] = nowyOrganizm;

	dodajKomunikat("Nowy organizm: " + gatunek + " narodzil sie na polu: " + nowyOrganizm->polozenieToString());
}

void Swiat::inicjujSwiat()
{
	stworzPlansze();
	dodajOrganizmy();
	wypelnijPlansze();
}

void Swiat::zapiszGre(bool& czyPoprawnyPrzycisk, bool& czyWyjsc)
{
	system("cls");
	wyswietlNaglowek();
	std::cout << "Panel zapisywania stanu gry" << std::endl << std::endl;

	std::string nazwaPliku;
	std::ofstream plik;

	std::cout << "Podaj nazwe pliku, w ktorym chcesz zapisac stan gry: ";
	std::cin >> nazwaPliku;
	plik.open(nazwaPliku);

	if (!plik.good())
		std::cout << "Nie udalo sie otworzyc pliku. Sprobuj ponownie pozniej." << std::endl;
	else
	{
		plik << "#Wymiary planszy" << std::endl;
		plik << dlugoscPlanszy << " " << szerokoscPlanszy << std::endl;
		plik << "#Numer tury" << std::endl;
		plik << nrTury << std::endl;

		plik << "#Parametry organizmow (gatunek, polozenie(x), polozenie(y), sila, wiek), dla czlowieka dodatkowo (czyAktywnaTarczaAlzura, czasTrwaniaUmiejetnosciSpecjalnej)" << std::endl;

		for (auto it = organizmy.begin(); it != organizmy.end(); ++it)
		{
			plik << (*it)->getGatunek() << " " << (*it)->getPolozenie().first << " " << (*it)->getPolozenie().second << " " << (*it)->getSila() << " " << (*it)->getWiek();

			if (*it == czlowiek)
				plik << " " << czlowiek->czyAktywnaTarczaAlzura() << " " << czlowiek->getCzasTrwaniaUmiejetnosciSpecjalnej();

			plik << std::endl;
		}

		plik.close();
	}

	std::cout << "Wcisnij R, aby wrocic do gry lub Q, aby wyjsc..." << std::endl;
	bool czyPoprawnyWybor = true;

	do
	{
		int wybor = _getch();
		czyPoprawnyWybor = true;

		switch (toupper(wybor))
		{
		case 'R':
			wyswietlWszystko();
			wyswietlKomunikatyDoSterowania();
			czyPoprawnyPrzycisk = false;
			break;
		case 'Q':
			czyWyjsc = true;
			break;
		default:
			std::cout << "Niepoprawny przycisk. Sprobuj ponownie" << std::endl;
			czyPoprawnyWybor = false;
		}
	} while (!czyPoprawnyWybor);

}

void Swiat::wczytajGre()
{
	system("cls");
	std::string nazwaPliku, linia;
	std::ifstream plik;

	std::cout << "Podaj nazwe pliku z zapisanym stanem gry: ";
	std::cin >> nazwaPliku;

	do
	{
		plik.open(nazwaPliku);

		if (!plik.good())
		{
			std::cout << "Plik nie istnieje lub nie udalo sie go odczytac. Sprobuj wpisac nazwe pliku ponownie lub wpisz Q, aby wyjsc: ";
			std::cin >> nazwaPliku;
		}

	} while (!plik.good() && nazwaPliku != "Q" && nazwaPliku != "q");

	if (plik.good())
	{
		int polozenieX, polozenieY, sila, wiek, czyAktywnaTarczaAlzura, czasTrwaniaUmiejetnosciSpecjalnej;
		std::string gatunek;

		getline(plik, linia);
		plik >> dlugoscPlanszy >> szerokoscPlanszy;
		plik.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		stworzPlansze();

		getline(plik, linia);
		plik >> nrTury;
		plik.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		getline(plik, linia);
		while (plik >> gatunek)
		{
			if (gatunek == "Wilcze" || gatunek == "Barszcz")
			{
				std::string gatunekDrugiCzlon;
				plik >> gatunekDrugiCzlon;

				gatunek += " " + gatunekDrugiCzlon;
			}
			
			plik >> polozenieX >> polozenieY >> sila >> wiek;

			stworzOrganizm(gatunek, std::make_pair(polozenieX, polozenieY));
			plansza[polozenieY][polozenieX]->setSila(sila);
			plansza[polozenieY][polozenieX]->setWiek(wiek);

			if (gatunek == "Czlowiek")
			{
				plik >> czyAktywnaTarczaAlzura >> czasTrwaniaUmiejetnosciSpecjalnej;
				czlowiek->setCzasTrwaniaUmiejetnosciSpecjalnej(czasTrwaniaUmiejetnosciSpecjalnej - 1); // -1, bo zostanie zwiêkszona po rozpoczêciu symulacji
				if (czyAktywnaTarczaAlzura == 1)
					czlowiek->aktywujTarczeAlzura();
			}
		}

		komunikaty.clear();
		symulacja();
	}

	plik.close();
}

void Swiat::rysujSwiat() const
{
	for (int i = 0; i < dlugoscPlanszy + 2; i++)
		std::cout << "# ";

	std::cout << std::endl; 

	for (int i = 0; i < szerokoscPlanszy; i++)
	{
		std::cout << "# ";

		for (int j = 0; j < dlugoscPlanszy; j++)
		{
			if (plansza[i][j] != nullptr)
				plansza[i][j]->rysowanie();
			else
				std::cout << ".";

			std::cout << " ";
		}
		
		std::cout << "#" << std::endl;
	}

	for (int i = 0; i < dlugoscPlanszy + 2; i++)
		std::cout << "# ";
}

int Swiat::getDlugoscPlanszy() const
{
	return dlugoscPlanszy;
}

int Swiat::getSzerokoscPlanszy() const
{
	return szerokoscPlanszy;
}

Organizm* Swiat::getOrganizmNaPlanszy(std::pair<int, int> pozycja) const
{
	return plansza[pozycja.second][pozycja.first];
}

bool Swiat::czyZajetePole(std::pair<int, int> pozycja) const
{
	if (plansza[pozycja.second][pozycja.first] != nullptr)
		return true;

	return false;
}

std::vector<std::pair<int, int>> Swiat::getSasiednieWolnePola(std::pair<int, int> polozenie) const
{
	std::vector<std::pair<int, int>> pola;

	if (polozenie.second > 0 && !czyZajetePole(std::make_pair(polozenie.first, polozenie.second - 1)))
		pola.push_back(std::make_pair(polozenie.first, polozenie.second - 1));
	if (polozenie.second < szerokoscPlanszy - 1 && !czyZajetePole(std::make_pair(polozenie.first, polozenie.second + 1)))
		pola.push_back(std::make_pair(polozenie.first, polozenie.second + 1));

	if (polozenie.first > 0 && !czyZajetePole(std::make_pair(polozenie.first - 1, polozenie.second)))
		pola.push_back(std::make_pair(polozenie.first - 1, polozenie.second));
	if (polozenie.first < dlugoscPlanszy - 1 && !czyZajetePole(std::make_pair(polozenie.first + 1, polozenie.second)))
		pola.push_back(std::make_pair(polozenie.first + 1, polozenie.second));

	return pola;
}

std::vector<std::pair<int, int>> Swiat::getSasiednieDowolnePola(std::pair<int, int> polozenie) const
{
	std::vector<std::pair<int, int>> pola;

	if (polozenie.second > 0)
		pola.push_back(std::make_pair(polozenie.first, polozenie.second - 1));
	if (polozenie.second < szerokoscPlanszy - 1)
		pola.push_back(std::make_pair(polozenie.first, polozenie.second + 1));

	if (polozenie.first > 0)
		pola.push_back(std::make_pair(polozenie.first - 1, polozenie.second));
	if (polozenie.first < dlugoscPlanszy - 1)
		pola.push_back(std::make_pair(polozenie.first + 1, polozenie.second));

	return pola;
}

void Swiat::aktualizujPolozenieNaPlanszy(std::pair<int, int> poprzedniePolozenie, std::pair<int, int> nowePolozenie)
{
	plansza[nowePolozenie.second][nowePolozenie.first] = plansza[poprzedniePolozenie.second][poprzedniePolozenie.first];
	plansza[poprzedniePolozenie.second][poprzedniePolozenie.first] = nullptr;
}

void Swiat::zamienOrganizmyNaPlanszy(std::pair<int, int> polozenie1, std::pair<int, int> polozenie2)
{
	Organizm* tmp = plansza[polozenie1.second][polozenie1.first];
	plansza[polozenie1.second][polozenie1.first] = plansza[polozenie2.second][polozenie2.first];
	plansza[polozenie2.second][polozenie2.first] = tmp;
}

void Swiat::usunOrganizmZPlanszy(std::pair<int, int> polozenie)
{
	plansza[polozenie.second][polozenie.first] = nullptr;
}
	
void Swiat::dodajKomunikat(std::string komunikat)
{
	komunikaty.push_back(komunikat);
}

void Swiat::wyswietlNaglowek() const
{
	std::cout << "========== SYMULATOR WIRTUALNEGO SWIATA ==========" << std::endl;
	std::cout << "======== Autor: Bartosz Lesniewski 184783 ========" << std::endl << std::endl;
}

void Swiat::wczytajDane()
{
	int dlugosc, szerokosc;
	std::cout << "Podaj dlugosc planszy: ";
	std::cin >> dlugosc;

	while (std::cin.fail() || dlugosc < 1)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');

		std::cout << "Podano nieprawdilowa wartosc. Sprobuj ponownie: ";
		std::cin >> dlugosc;
	}

	std::cout << "Podaj szerokosc planszy: ";
	std::cin >> szerokosc;
	while (std::cin.fail() || szerokosc < 1)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');

		std::cout << "Podano nieprawdilowa wartosc. Sprobuj ponownie: ";
		std::cin >> szerokosc;
	}

	dlugoscPlanszy = dlugosc;
	szerokoscPlanszy = szerokosc;
}

void Swiat::wybierzOpcje()
{
	std::cout << std::endl << "Wpisz litere odpowiadajaca wlasciwej opcji: ";
	bool czyPrawidlowyWybor = true;
	char wybor = ' ';

	do
	{
		std::cin >> wybor;
		wybor = toupper(wybor);
		czyPrawidlowyWybor = true;

		if (wybor == 'N')
		{
			wczytajDane();
			inicjujSwiat();
			symulacja();
		}

		else if (wybor == 'W')
			wczytajGre();

		else if (wybor != 'Q')
		{
			std::cout << "Nieprawidlowa opcja. Sprobuj ponownie: ";
			czyPrawidlowyWybor = false;
		}

	} while (!czyPrawidlowyWybor);
}

void Swiat::menu()
{
	wyswietlNaglowek();
	std::cout << "MENU" << std::endl;
	std::cout << "N - nowa gra" << std::endl;
	std::cout << "W - wczytaj gre" << std::endl;
	std::cout << "Q - wyjscie" << std::endl;
	wybierzOpcje();
}

void Swiat::sortujOrganizmy()
{
	std::sort(organizmy.begin(), organizmy.end(), 
		[](Organizm* org1, Organizm* org2) 
		{ 
			if (org1->getInicjatywa() != org2->getInicjatywa())
				return org1->getInicjatywa() > org2->getInicjatywa(); 

			return org1->getWiek() > org2->getWiek();
		});
}

void Swiat::aktualizujWiekOrganizmow()
{
	for (auto it = organizmy.begin(); it != organizmy.end(); ++it)
		(*it)->setWiek((*it)->getWiek() + 1);
}

void Swiat::wykonajTure()
{
	aktualizujWiekOrganizmow();
	sortujOrganizmy();

	int iloscOrganizmow = organizmy.size();

	for (int i = 0; i < iloscOrganizmow; i++)
	{
		if (organizmy[i]->sprawdzCzyZyje())
			organizmy[i]->akcja();
	}

	// usuwa nie¿ywe organizmy
	for (auto it = organizmy.begin(); it != organizmy.end();)
	{
		if ((*it)->sprawdzCzyZyje() == false)
		{
			if (*it == czlowiek)
				czlowiek = nullptr;
		
			delete* it;
			it = organizmy.erase(it);
		}
		else
			++it;
	}
}

void Swiat::wyswietlInstrukcje() const
{
	std::cout << "Podstawowe sterowanie: " << std::endl;
	std::cout << "Strzalki - poruszanie czlowiekiem" << std::endl << "X - aktywacja umiejetnosci specjalnej czlowieka" << std::endl << "Spacja - przejscie do nastepnej tury (bez ruchu czlowieka)" << std::endl << "S - zapisanie aktualnego stanu gry" << std::endl << "Q - wyjscie" << std::endl;
}

void Swiat::nadajKierunekCzlowiekowi(Kierunek kierunek, bool& czyPoprawnyPrzycisk)
{
	if (czlowiek->czyMozliwyRuch(kierunek, 1))
		czlowiek->setKierunekRuchu(kierunek);
	else
	{
		std::cout << "Nie mozna wykonac ruchu w te strone. Sprobuj ponownie..." << std::endl;
		czyPoprawnyPrzycisk = false;
	}
}

void Swiat::poruszanieCzlowiekiem(int akcja, bool &czyPoprawnyPrzycisk)
{
	if (czlowiek != nullptr)
	{
		switch (akcja)
		{
		case STRZALKA_LEWO:
			nadajKierunekCzlowiekowi(Kierunek::LEWO, czyPoprawnyPrzycisk);
			break;
		case STRZALKA_PRAWO:
			nadajKierunekCzlowiekowi(Kierunek::PRAWO, czyPoprawnyPrzycisk);
			break;
		case STRZALKA_GORA:
			nadajKierunekCzlowiekowi(Kierunek::GORA, czyPoprawnyPrzycisk);
			break;
		case STRZALKA_DOL:
			nadajKierunekCzlowiekowi(Kierunek::DOL, czyPoprawnyPrzycisk);
			break;
		default:
			std::cout << "Nieprawidlowy przycisk. Sprobuj ponownie..." << std::endl;
			czyPoprawnyPrzycisk = false;
			break;
		}
	}
	else
	{
		std::cout << "Nieprawidlowy przycisk. Sprobuj ponownie..." << std::endl;
		czyPoprawnyPrzycisk = false;
	}
}

void Swiat::wyswietlKomunikatyDoSterowania()
{
	std::cout << std::endl;

	if (czlowiek != nullptr)
	{
		if (czlowiek->czyAktywnaTarczaAlzura())
		{
			czlowiek->setCzasTrwaniaUmiejetnosciSpecjalnej(czlowiek->getCzasTrwaniaUmiejetnosciSpecjalnej() + 1);

			if (czlowiek->getCzasTrwaniaUmiejetnosciSpecjalnej() == 5)
			{
				czlowiek->dezaktywujTarczeAlzura();
				std::cout << "Specjalna umiejetnosc czlowieka - Tarcza Alzura - zostala dezaktywowana." << std::endl;
			}
			else
			{
				std::cout << "Specjalna umiejetnosc czlowieka - Tarcza Alzura - jest aktywna. Pozostaly czas: " << 5 - czlowiek->getCzasTrwaniaUmiejetnosciSpecjalnej() << " tur(y)." << std::endl;
			}
		}
		else
		{
			if (czlowiek->getCzasTrwaniaUmiejetnosciSpecjalnej() > 0)
				czlowiek->setCzasTrwaniaUmiejetnosciSpecjalnej(czlowiek->getCzasTrwaniaUmiejetnosciSpecjalnej() - 1);
		}

		std::cout << "Wcisnij odpowiedni klawisz..." << std::endl;
	}
	else
		std::cout << "Czlowiek nie zyje. Wcisnij spacje, aby przejsc do nastepnej tury..." << std::endl;
}

bool Swiat::sterowanie()
{
	wyswietlKomunikatyDoSterowania();

	bool czyPoprawnyPrzycisk = true, czyWyjsc = false;

	do
	{
		int akcja = _getch();
		czyPoprawnyPrzycisk = true;

		if (akcja == 0 || akcja == 224)
		{
			akcja = _getch();
			poruszanieCzlowiekiem(akcja, czyPoprawnyPrzycisk);
		}
		else
		{
			switch (toupper(akcja))
			{
			case 'Q':
				czyWyjsc = true;
				break;
			case 'S':
				zapiszGre(czyPoprawnyPrzycisk, czyWyjsc);
				break;
			case 'X':
			{
				if (czlowiek != nullptr)
				{
					if (czlowiek->getCzasTrwaniaUmiejetnosciSpecjalnej() > 0)
						std::cout << "Nie mozna aktywowac specjalnej umiejetnosci czlowieka - Tarcza Alzura. Ponowna aktywacja bedzie mozliwa za " << czlowiek->getCzasTrwaniaUmiejetnosciSpecjalnej() << " tur." << std::endl;
					else if (czlowiek->czyAktywnaTarczaAlzura())
						std::cout << "Specjalna umiejetnosc czlowieka - Tarcza Alzura - jest juz aktywna." << std::endl;
					else
					{
						std::cout << "Specjalna umiejetnosc czlowieka - Tarcza Alzura - zostala aktywowana." << std::endl;
						czlowiek->aktywujTarczeAlzura();
					}
				}
				else
					std::cout << "Nie mozna aktywowac umiejetnosci specjalnej - czlowiek nie zyje." << std::endl;

				czyPoprawnyPrzycisk = false;
				break;
			}
			case SPACJA:
				czyPoprawnyPrzycisk = true;
				break;
			default:
				std::cout << "Nieprawidlowy przycisk. Sprobuj ponownie..." << std::endl;
				czyPoprawnyPrzycisk = false;
				break;
			}
		}

	} while (!czyPoprawnyPrzycisk);
	
	return czyWyjsc;
}

void Swiat::wyswietlKomunikaty()
{
	std::cout << std::endl << std::endl;

	for (auto it = komunikaty.begin(); it != komunikaty.end(); ++it)
		std::cout << *it << std::endl;
	
	komunikaty.clear();
}

void Swiat::wyswietlWszystko()
{
	system("cls");
	wyswietlNaglowek();
	wyswietlInstrukcje();
	std::cout << std::endl << "Tura: " << nrTury << std::endl << std::endl;
	rysujSwiat();
	wyswietlKomunikaty();
}

void Swiat::symulacja()
{
	bool wyjscie = false;

	do
	{
		wyswietlWszystko();

		wyjscie = sterowanie();

		if (!wyjscie)
		{
			wykonajTure();
			nrTury++;
		}

	} while (!wyjscie);
}