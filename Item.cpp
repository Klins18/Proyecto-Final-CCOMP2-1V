#include "Item.h"

Item::Item()
{
	this->itemtipo = -1;
	this->nombre = "VACIO";
	this->nivel = 0;
	this->buyval = 0;
	this->sellval = 0;
	this->rareza = -1;
}

Item::Item(int itemtipo, int nivel, int rareza)
{
	this->nombre = "RANDOM";
	this->nivel = rand() % (nivel+2) + 1;
	this->rareza = rareza;
	this->buyval = (this->nivel + this->rareza) + this->nivel*this->rareza*10;
	this->sellval = this->buyval / 2;
	this->itemtipo = itemtipo;
}

Item::Item(int itemtipo, std::string nombre, int nivel, int buyval, int sellval, int rareza)
{
	this->itemtipo = itemtipo;
	this->nombre = nombre;
	this->nivel = nivel;
	this->buyval = buyval;
	this->sellval = sellval;
	this->rareza = rareza;
}

Item::~Item()
{

}