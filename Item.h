#pragma once

#include"STLINCLUDE.h"

enum tipoItem {arma = 0, armadura};

class Item
{
private:
	int itemtipo;
	std::string nombre;
	int nivel;
	int buyval;
	int sellval;
	int rareza;

public:
	Item();
	Item(
		int itemtipo,
		int nivel, 
		int rareza
	);
	Item(
		int itemtipo,
		std::string nombre, 
		int nivel, 
		int buyval,
		int sellval, 
		int rareza);
	virtual ~Item();

	inline std::string debugPrint() const { return this->nombre; }
	virtual Item* clone()const = 0;
	virtual std::string toString()const = 0;
	virtual std::string toStringSave()const = 0;

	//Accessors
	inline const std::string& getnombre() const { return this->nombre; }
	inline const int& getnivel() const { return this->nivel; }
	inline const int& getBuyval() const { return this->buyval; }
	inline const int& getSellval() const { return this->sellval; }
	inline const int& getRareza() const { return this->rareza; }
	inline const int& getTipoItem() const { return this->itemtipo; }

	//Modifiers
	inline void setnombre(std::string nombre) { this->nombre = nombre; }
};

enum rareza {
	COMMON = 0, 
	UNCOMMON, 
	RARE, 
	LEGENDARY,
	MYTHIC
};