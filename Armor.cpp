#include"Armor.h"
#include"Weapon.h"

dArr<std::string> Armadura::nombres;

void Armadura::initnombres()
{
	Armadura::nombres.push("Angel de la Guarda");
	Armadura::nombres.push("Capucha de lana");
	Armadura::nombres.push("Defensa Recia");
	Armadura::nombres.push("Armadura del Caos");
	Armadura::nombres.push("Placas de Hierro");
	Armadura::nombres.push("Dagas de Asesino");
}

Armadura::Armadura()
	:Item()
{
	this->tipo = -1;
	this->defensa = 0;
}

Armadura::Armadura(int nivel, int rareza)
	:Item(tipoItem::armadura, nivel, rareza)
{
	this->defensa = rand() % (nivel * (rareza+1));
	this->defensa += (rareza + 1) * 5;
	this->tipo = rand() % 4;
	
	switch (this->tipo)
	{
	case TipoArmadura::CASCO:
		this->tipoStr = "CASCO";
			break;
	case TipoArmadura::PETO:
		this->tipoStr = "PETO";
			break;
	case TipoArmadura::GUANTES:
		this->tipoStr = "GUANTES";
			break;
	case TipoArmadura::PERNERAS:
		this->tipoStr = "PERNERAS";
			break;
	default:
		this->tipoStr = "ERROR - INVALIDO!";
			break;
	}

	this->setnombre(Armadura::nombres[rand() % Armadura::nombres.size()]);

	if(rareza == 3)
		this->defensa += nivel * 5;
	else if (rareza == 4)
		this->defensa += nivel * 10;
}

Armadura::Armadura(int tipo, int defensa, std::string nombre, int nivel, int buyval, int sellval, int rareza)
	: Item(tipoItem::armadura, nombre, nivel, buyval, sellval, rareza)
{
	this->tipo = tipo;
	this->defensa = defensa;
}

Armadura::~Armadura()
{

}
	
Armadura* Armadura::clone()const
{
	return new Armadura(*this);
}

std::string Armadura::toString()const
{
	std::string str = 
		this->getnombre()
		+ " | tipo: "
		+ this->tipoStr
		+ " | Lvl: "
		+ std::to_string(this->getnivel())
		+ " | rareza: "
		+ std::to_string(this->getRareza())
		+ " | Def: "
		+ std::to_string(this->defensa);

	return str;
}

std::string Armadura::toStringSave()const
{
	std::string str =
		std::to_string(this->getTipoItem())
		+ " "
		+ this->getnombre()
		+ " "
		+ std::to_string(this->getnivel())
		+ " "
		+ std::to_string(this->getRareza())
		+ " "
		+ std::to_string(this->getBuyval())
		+ " "
		+ std::to_string(this->getSellval())
		+ " "
		+ std::to_string(this->defensa)
		+ " "
		+ std::to_string(this->tipo)
		+ " ";

	return str;
}