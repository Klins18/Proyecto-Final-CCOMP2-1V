#include"Weapon.h"

dArr<std::string> Arma::nombres;

void Arma::initnombres()
{
	Arma::nombres.push("Butter-Knife");
	Arma::nombres.push("Leaf-Cutter");
	Arma::nombres.push("Face-Shredder");
	Arma::nombres.push("Bro-Knife");
	Arma::nombres.push("Katana-Sword");
	Arma::nombres.push("Brutal-Murder");
}

Arma::Arma()
	:Item()
{
	this->danoMax = 0;
	this->danoMin = 0;
}

Arma::Arma(int nivel, int rareza)
	:Item(tipoItem::arma, nivel, rareza)
{
	this->danoMax = rand() % nivel * (rareza+1);
	this->danoMax += (rareza+1) * 5;
	this->setnombre(Arma::nombres[rand() % Arma::nombres.size()]);

	if (rareza == 3)
		this->danoMax += nivel * 5;
	else if (rareza == 4)
		this->danoMax += nivel * 10;

	this->danoMin = this->danoMax / 2;
}

Arma::Arma(int danoMin, int danoMax, std::string nombre, int nivel, int buyval, int sellval, int rareza)
	: Item(tipoItem::arma, nombre, nivel, buyval, sellval, rareza)
{
	this->danoMin = danoMin;
	this->danoMax = danoMax;
}

Arma::~Arma()
{

}

Arma* Arma::clone()const
{
	return new Arma(*this);
}

std::string Arma::toString()const
{
	std::string str =
		this->getnombre()
		+ " | Lvl: "
		+ std::to_string(this->getnivel())
		+ " | rareza: "
		+ std::to_string(this->getRareza())
		+ " | Damage: "
		+ std::to_string(this->danoMin)
		+ " - "
		+ std::to_string(this->danoMax);

	return str;
}

std::string Arma::toStringSave()const
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
		+ std::to_string(this->danoMin)
		+ " "
		+ std::to_string(this->danoMax)
		+ " ";

	return str;
}