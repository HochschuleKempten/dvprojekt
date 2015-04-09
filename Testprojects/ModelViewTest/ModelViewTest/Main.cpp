#pragma once

#include "MKraftwerke.h"
#include "VKohlekraftwerk.h"
#include <list>

static int savegame[2] = { 0, 0 };

template<typename ClassVKohlekraftwerk>
class MSpielfeld
{
	std::list<MKraftwerke*> models;

public:
	void ladeSpiel()
	{
		for (int i : savegame) {
			if (i == 0) {
				models.push_back(new MKohlekraftwerk<ClassVKohlekraftwerk>());
			}
		}
	}

	void goKraftwerke()
	{
		for (MKraftwerke* m : models) {
			m->myCoolFunction();
			delete m;
		}
	}
};

template<typename ClassVKohlekraftwerk>
class MMaster
{
public:
	MSpielfeld<ClassVKohlekraftwerk> spielfeld;
};

int main()
{
	MMaster<VKohlekraftwerk> m;

	m.spielfeld.ladeSpiel();
	m.spielfeld.goKraftwerke();
}
