#include "Character.h"
#include "Game.h"
#include <cmath>
Game game;
Personaje::Personaje()
{
	this->distanciaViajada = 0;

	this->oro = 0;

	this->nombre = "";
	this->nivel = 0;
	this->exp = 0;
	this->expSub = 0;

	this->fuerza = 0;
	this->vitalidad = 0;
	this->reflejos = 0;
	this->inteligencia = 0;

	this->vida = 0;
	this->vidaMax = 0;
	this->energia = 0;
	this->energiaMax = 0;
	this->danoMin = 0;
	this->danoMax = 0;
	this->defensa = 0;
	this->presicion = 0;
	this->suerte = 0;

	this->estadisticasPts = 0;
}

Personaje::Personaje(std::string nombre, int distanciaViajada,
	int oro, int nivel,
	int exp, int fuerza, int vitalidad, 
	int reflejos, int inteligencia,
	int vida, int energia, int estadisticasPts)
{
	this->distanciaViajada = distanciaViajada;

	this->oro = oro;

	this->nombre = nombre;
	this->nivel = nivel;
	this->exp = exp;
	this->expSub = 0;

	this->fuerza = fuerza;
	this->vitalidad = vitalidad;
	this->reflejos = reflejos;
	this->inteligencia = inteligencia;

	this->vida = vida;
	this->vidaMax = 0;
	this->energia = energia;
	this->energiaMax = 0;
	this->danoMin = 0;
	this->danoMax = 0;
	this->defensa = 0;
	this->presicion = 0;
	this->suerte = 0;

	this->estadisticasPts = estadisticasPts;

	this->nuevStats();
}

Personaje::~Personaje()
{

}

//Functions
void Personaje::init(const std::string nombre)
{
	this->distanciaViajada = 0;

	this->oro = 100;

	this->nombre = nombre;
	this->nivel = 1;
	this->exp = 0;

	this->fuerza = 5;
	this->vitalidad = 5;
	this->reflejos = 5;
	this->inteligencia = 5;

	this->estadisticasPts = 0;

	this->nuevStats();
}

void Personaje::display() const
{
	std::cout << "= Hoja de Personaje =" << "\n";
	std::cout << "= Nombre: " << this->nombre << "\n";
	std::cout << "= Nivel: " << this->nivel << "\n";
	std::cout << "= Exp: " << this->exp << "\n";
	std::cout << "= Exp to next nivel: " << this->expSub << "\n";
	std::cout << "= EstadisticasPts: " << this->estadisticasPts << "\n";
	std::cout << "\n";
	std::cout << "= Fuerza: " << this->fuerza << "\n";
	std::cout << "= Vitalidad: " << this->vitalidad << "\n";
	std::cout << "= Reflejos: " << this->reflejos << "\n";
	std::cout << "= Inteligencia: " << this->inteligencia << "\n";
	std::cout << "\n";
	std::cout << "= Vida: " << this->vida << " / " << this->vidaMax << "\n";
	std::cout << "= Energia: " << this->energia << " / " << this->energiaMax << "\n";
	std::cout << "= Danio: " << this->danoMin << "( +" << this->armaaa.getdanoMin() << ")" << " - "<< this->danoMax << "( +" << this->armaaa.getdanoMax() << ")" << "\n";
	std::cout << "= Defensa: " << this->defensa << "( +" << std::to_string(this->getSumaDefensa()) << ")" << "\n";
	std::cout << "= Presicion: " << this->presicion << "\n";
	std::cout << "= Suerte: " << this->suerte << "\n";
	std::cout << "\n";
	std::cout << "= Distance Travelled: " << this->distanciaViajada << "\n";
	std::cout << "= Oro: " << this->oro << "\n";
	std::cout << "\n";
	std::cout << "= Arma: " << this->armaaa.getnombre()
		<< " Lvl: " << this->armaaa.getnivel()
		<< " Danio: " << this->armaaa.getdanoMin() << " - " << this->armaaa.getdanoMax() << "\n";
	std::cout << "= Armadura CASCO: " << this->casco.getnombre()
		<< " Lvl: " << this->casco.getnivel()
		<< " Def: " << this->casco.getDefensa() << "\n";
	std::cout << "= Armadura PETO: " << this->peto.getnombre()
		<< " Lvl: " << this->peto.getnivel()
		<< " Def: " << this->peto.getDefensa() << "\n";
	std::cout << "= Armadura GUANTES: " << this->guantes.getnombre()
		<< " Lvl: " << this->guantes.getnivel()
		<< " Def: " << this->guantes.getDefensa() << "\n";
	std::cout << "= Armadura PERNERAS: " << this->perneras.getnombre()
		<< " Lvl: " << this->perneras.getnivel()
		<< " Def: " << this->perneras.getDefensa() << "\n" << "\n";
}

std::string Personaje::getAsString() const
{
	return nombre + " "
		+ std::to_string(distanciaViajada) + " "
		+ std::to_string(oro) + " "
		+ std::to_string(nivel) + " "
		+ std::to_string(exp) + " "
		+ std::to_string(fuerza) + " "
		+ std::to_string(vitalidad) + " "
		+ std::to_string(reflejos) + " "
		+ std::to_string(inteligencia) + " "
		+ std::to_string(vida) + " "
		+ std::to_string(energia) + " "
		+ std::to_string(estadisticasPts) + " "
		+ this->armaaa.toStringSave()
		+ this->casco.toStringSave()
		+ this->peto.toStringSave()
		+ this->guantes.toStringSave()
		+ this->perneras.toStringSave();
}

std::string Personaje::getInvAsString(bool tienda)
{
	std::string inv;

	for (size_t i = 0; i < this->inventario.size(); i++)
	{
		if (tienda)
		{
			inv += std::to_string(i) + ": " + this->inventario[i].toString() + "\n" + " - Vender val: "
				+ std::to_string(this->inventario[i].getSellval()) + "\n";
		}
		else
		{
			inv += std::to_string(i) + ": " + this->inventario[i].toString() + "\n";
		}
	}

	return inv;
}

std::string Personaje::getInvAsStringSave()
{
	std::string inv;

	for (size_t i = 0; i < this->inventario.size(); i++)
	{
		if(this->inventario[i].getTipoItem() == tipoItem::arma)
			inv += this->inventario[i].toStringSave();
	}

	inv += "\n";

	for (size_t i = 0; i < this->inventario.size(); i++)
	{
		if (this->inventario[i].getTipoItem() == tipoItem::armadura)
			inv += this->inventario[i].toStringSave();
	}

	return inv;
}

void Personaje::subidaNvl()
{
	if (this->exp >= this->expSub)
	{
		this->exp -= this->expSub;
		this->nivel++;
		this->expSub = static_cast<int>((50 / 3)*((pow(nivel, 3)
			- 6 * pow(nivel, 2))
			+ 17 * nivel - 12)) + 100;

		this->estadisticasPts++;

		this->nuevStats();

		std::cout << "Eres Nivel:  " << this->nivel << "!" << "\n\n";
	}
	else
	{
		std::cout << "EXP INSUFICIENTE!" << "\n\n";
	}
}

void Personaje::nuevStats()
{
	this->expSub = static_cast<int>(
		(50 / 3)*((pow(nivel, 3)
			- 6 * pow(nivel, 2))
			+ 17 * nivel - 12)) + 100;

	this->vidaMax = (this->vitalidad * 5) + (this->fuerza) + this->nivel*5;
	this->energiaMax = this->vitalidad + (this->fuerza / 2) + (this->reflejos / 3);
	this->energia = this->energiaMax;
	this->danoMin = this->fuerza;
	this->danoMax = this->fuerza + 2;
	this->defensa = this->reflejos + (this->inteligencia / 2);
	this->presicion = (this->reflejos / 2) + inteligencia;
	this->suerte = this->inteligencia;

	this->vida = this->vidaMax;
}

void Personaje::addStats(int stat, int val)
{
	if (this->estadisticasPts < val)
		std::cout << "ERROR! estadisticasPts! Insuficientes" << "\n";
	else
	{
		switch (stat)
		{
		case 0:
			this->fuerza += val;
			std::cout << "FUERZA MEJORADA!" << "\n";

			break;

		case 1:
			this->vitalidad += val;
			std::cout << "VITALIDAD MEJORADA!" << "\n";
			break;

		case 2:
			this->reflejos += val;
			std::cout << "REFLEJOS MEJORADA!" << "\n";
			break;

		case 3:
			this->inteligencia += val;
			std::cout << "INTELIGENCIA MEJORADA!" << "\n";
			break;

		default:
			std::cout << "NO HAY ESTADISTICA!" << "\n";
			break;
		}

		this->estadisticasPts -= val;

		this->nuevStats();
	}
}

void Personaje::equiparItem(unsigned index)
{
	if (index < 0 || index >= this->inventario.size())
	{
		std::cout << "Item invalido!" << "\n\n";
	}
	else
	{
		Arma *w = nullptr;
		w = dynamic_cast<Arma*>(&this->inventario[index]);

		Armadura *a = nullptr;
		a = dynamic_cast<Armadura*>(&this->inventario[index]);

		//Is arma
		if (w != nullptr)
		{
			if (this->armaaa.getRareza() >= 0)
				this->inventario.addItem(this->armaaa);
			this->armaaa = *w;
			this->inventario.removeItem(index);
		}
		else if (a != nullptr)
		{
			switch (a->getTipo())
			{
			case TipoArmadura::CASCO:
				if (this->casco.getRareza() >= 0)
					this->inventario.addItem(this->casco);
				this->casco = *a;
				this->inventario.removeItem(index);
				break;
			case TipoArmadura::PETO:
				if (this->peto.getRareza() >= 0)
					this->inventario.addItem(this->peto);
				this->peto = *a;
				this->inventario.removeItem(index);
				break;
			case TipoArmadura::GUANTES:
				if (this->guantes.getRareza() >= 0)
					this->inventario.addItem(this->guantes);
				this->guantes = *a;
				this->inventario.removeItem(index);
				break;
			case TipoArmadura::PERNERAS:
				if(this->perneras.getRareza() >= 0)
					this->inventario.addItem(this->perneras);
				this->perneras = *a;
				this->inventario.removeItem(index);
				break;
			default:
				std::cout << "ERROR TIPO DE ARMADURA INVALIDA!" << "\n\n";
				break;
			}
		}
		else
		{
			std::cout << "ERROR AL EQUIPAR, EL ITEM NO ES UNA ARMADURA O UN ARMA!";
		}
	}
}

void Personaje::removeItem(const int index)
{
	if (index < 0 || index >= this->inventario.size())
		std::cout << "ERROR,NO ES POSIBLE QUITAR EL ITEM" << "\n\n";
	else
	{
		this->inventario.removeItem(index);
	}
}

const Item& Personaje::getItem(const int index)
{
	if (index < 0 || index >= this->inventario.size())
	{
		std::cout << "ERROR, NO ES POSIBLE RETIRAR EL ITEM" << "\n\n";
		throw("ERROR FUERA DE LIMITES");
	}

	return this->inventario[index];
}

void Personaje::tomaDano(const int damage)
{
	this->vida -= damage;

	if (this->vida <= 0)
	{
		this->vida = 0;
	}
}