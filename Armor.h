#pragma once

#include"STLINCLUDE.h"
#include"Item.h"

enum TipoArmadura { CASCO = 0, PETO, GUANTES, PERNERAS };

class Armadura :
	public Item
{
private:
	int tipo;
	std::string tipoStr;
	int defensa;

public:
	Armadura();
	Armadura(
		int nivel, 
		int rareza
	);
	Armadura(
		int tipo, 
		int defensa,
		std::string nombre, 
		int nivel, 
		int buyval,
		int sellval,
		int rareza
	);
	virtual ~Armadura();

	//Pure virtual
	virtual Armadura* clone()const;

	//Functions
	std::string toString()const;
	std::string toStringSave()const;

	//Accessors
	inline int getDefensa()const { return this->defensa; }
	inline int getTipo()const { return this->tipo; }

	//Static
	static dArr<std::string> nombres;
	static void initnombres();
};