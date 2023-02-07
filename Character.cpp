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

Personaje::Personaje(string nombre, int distanciaViajada,
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
void Personaje::init(const string nombre)
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
	cout << "= Hoja de Personaje =" << "\n";
	cout << "= Nombre: " << this->nombre << "\n";
	cout << "= Nivel: " << this->nivel << "\n";
	cout << "= Exp: " << this->exp << "\n";
	cout << "= Exp to next nivel: " << this->expSub << "\n";
	cout << "= EstadisticasPts: " << this->estadisticasPts << "\n";
	cout << "\n";
	cout << "= Fuerza: " << this->fuerza << "\n";
	cout << "= Vitalidad: " << this->vitalidad << "\n";
	cout << "= Reflejos: " << this->reflejos << "\n";
	cout << "= Inteligencia: " << this->inteligencia << "\n";
	cout << "\n";
	cout << "= Vida: " << this->vida << " / " << this->vidaMax << "\n";
	cout << "= Energia: " << this->energia << " / " << this->energiaMax << "\n";
	cout << "= Danio: " << this->danoMin << "( +" << this->armaaa.getdanoMin() << ")" << " - "<< this->danoMax << "( +" << this->armaaa.getdanoMax() << ")" << "\n";
	cout << "= Defensa: " << this->defensa << "( +" << std::to_string(this->getSumaDefensa()) << ")" << "\n";
	cout << "= Presicion: " << this->presicion << "\n";
	cout << "= Suerte: " << this->suerte << "\n";
	cout << "\n";
	cout << "= Distance Travelled: " << this->distanciaViajada << "\n";
	cout << "= Oro: " << this->oro << "\n";
	cout << "\n";
	cout << "= Arma: " << this->armaaa.getnombre()
		<< " Lvl: " << this->armaaa.getnivel()
		<< " Danio: " << this->armaaa.getdanoMin() << " - " << this->armaaa.getdanoMax() << "\n";
	cout << "= Armadura CASCO: " << this->casco.getnombre()
		<< " Lvl: " << this->casco.getnivel()
		<< " Def: " << this->casco.getDefensa() << "\n";
	cout << "= Armadura PETO: " << this->peto.getnombre()
		<< " Lvl: " << this->peto.getnivel()
		<< " Def: " << this->peto.getDefensa() << "\n";
	cout << "= Armadura GUANTES: " << this->guantes.getnombre()
		<< " Lvl: " << this->guantes.getnivel()
		<< " Def: " << this->guantes.getDefensa() << "\n";
	cout << "= Armadura PERNERAS: " << this->perneras.getnombre()
		<< " Lvl: " << this->perneras.getnivel()
		<< " Def: " << this->perneras.getDefensa() << "\n" << "\n";
}

string Personaje::getAsString() const
{
	return nombre + " "
		+ to_string(distanciaViajada) + " "
		+ to_string(oro) + " "
		+ to_string(nivel) + " "
		+ to_string(exp) + " "
		+ to_string(fuerza) + " "
		+ to_string(vitalidad) + " "
		+ to_string(reflejos) + " "
		+ to_string(inteligencia) + " "
		+ to_string(vida) + " "
		+ to_string(energia) + " "
		+ to_string(estadisticasPts) + " "
		+ this->armaaa.toStringSave()
		+ this->casco.toStringSave()
		+ this->peto.toStringSave()
		+ this->guantes.toStringSave()
		+ this->perneras.toStringSave();
}

string Personaje::getInvAsString(bool tienda)
{
	string inv;

	for (size_t i = 0; i < this->inventario.size(); i++)
	{
		if (tienda)
		{
			inv += to_string(i) + ": " + this->inventario[i].toString() + "\n" + " - Vender val: "
				+ std::to_string(this->inventario[i].getSellval()) + "\n";
		}
		else
		{
			inv += to_string(i) + ": " + this->inventario[i].toString() + "\n";
		}
	}

	return inv;
}

string Personaje::getInvAsStringSave()
{
	string inv;

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

		cout << "Eres Nivel:  " << this->nivel << "!" << "\n\n";
	}
	else
	{
		cout << "EXP INSUFICIENTE!" << "\n\n";
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
		cout << "ERROR! estadisticasPts! Insuficientes" << "\n";
	else
	{
		switch (stat)
		{
		case 0:
			this->fuerza += val;
			cout << "FUERZA MEJORADA!" << "\n";

			break;

		case 1:
			this->vitalidad += val;
			cout << "VITALIDAD MEJORADA!" << "\n";
			break;

		case 2:
			this->reflejos += val;
			cout << "REFLEJOS MEJORADA!" << "\n";
			break;

		case 3:
			this->inteligencia += val;
			cout << "INTELIGENCIA MEJORADA!" << "\n";
			break;

		default:
			cout << "NO HAY ESTADISTICA!" << "\n";
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
		cout << "Item invalido!" << "\n\n";
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
				cout << "ERROR TIPO DE ARMADURA INVALIDA!" << "\n\n";
				break;
			}
		}
		else
		{
			cout << "ERROR AL EQUIPAR, EL ITEM NO ES UNA ARMADURA O UN ARMA!";
		}
	}
}

void Personaje::removeItem(const int index)
{
	if (index < 0 || index >= this->inventario.size())
		cout << "ERROR,NO ES POSIBLE QUITAR EL ITEM" << "\n\n";
	else
	{
		this->inventario.removeItem(index);
	}
}

const Item& Personaje::getItem(const int index)
{
	if (index < 0 || index >= this->inventario.size())
	{
		cout << "ERROR, NO ES POSIBLE RETIRAR EL ITEM" << "\n\n";
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