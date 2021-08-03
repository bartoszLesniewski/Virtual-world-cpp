#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Swiat.h"

int main()
{
	srand(time(NULL));

	Swiat swiat;
	//swiat.rysujSwiat();
	swiat.menu();
}