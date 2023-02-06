#pragma once

#include"STLINCLUDE.h"

#include"Character.h"
#include"Enemy.h"
#include"Puzzle.h"
#include"Boss.h"


class Event
{
private:

public:
	Event();
	virtual ~Event();
	void generateEvent(Personaje &personaje, dArr<Enemy>& enemies);

	//Events
	void tiendaEncouter(Personaje &personaje);
	void enemyEncouter(Personaje &personaje, dArr<Enemy>& enemies);
	void puzzleEncouter(Personaje &personaje);
	void bossEncouter(Personaje &personaje, Boss & boss);

	//statics
	static int nrOfEvents;
};
