#pragma once

#include"STLINCLUDE.h"

class Enemy
{
private:
	int nivel;
	int vida;
	int vidaMax;
	int danoMin;
	int danoMax;
	float dropChance;
	int defensa;
	int presicion;

public:
	Enemy(int nivel = 0);
	virtual ~Enemy();

	inline bool estaVivo() { return this->vida > 0; }
	std::string getAsString()const;
	void tomaDano(int damage);

	inline int getnivel()const { return this->nivel; }
	inline int getdanoMin()const { return this->danoMin; }
	inline int getdanoMax()const { return this->danoMax; }
	inline int getDamage()const { return rand() % this->danoMax + this->danoMin; }
	inline int getExp()const { return this->nivel * 100; }
	inline int getvida()const { return this->vida; }
	inline int getvidaMax()const { return this->vidaMax; }
	inline int getdefensa()const { return this->defensa; }
	inline int getpresicion()const { return this->presicion; }
};