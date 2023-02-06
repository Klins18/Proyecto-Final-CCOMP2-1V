#pragma once

#include"STLINCLUDE.h"
#include"Item.h"

class Arma :
	public Item
{
private:
	int danoMin;
	int danoMax;

public:
	Arma();
	Arma(
		int nivel, 
		int rareza
	);
	Arma(
		int danoMin, 
		int danoMax,
		std::string nombre, 
		int nivel, 
		int buyval, 
		int sellval, 
		int rareza);
	virtual ~Arma();

	//Pure virtual
	virtual Arma* clone()const;

	//Functions
	std::string toString()const;
	std::string toStringSave()const;

	//Accessors
	inline int getdanoMin()const { return this->danoMin; }
	inline int getdanoMax()const { return this->danoMax; }

	//Modifiers

	//Static
	static dArr<std::string> nombres;
	static void initnombres();
};