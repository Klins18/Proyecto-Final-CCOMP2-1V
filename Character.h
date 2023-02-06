#pragma once

#include"STLINCLUDE.h"
#include"Inventory.h"
#include"Weapon.h"
#include"Armor.h"
#include <cmath>

using namespace std;

class Personaje
{
private:

	int distanciaViajada; // distanceTravelled

	Inventario inventario; // inventario
	Arma armaaa; // arma
	Armadura casco; //casco
	Armadura peto;// peto
	Armadura guantes; //guantes
	Armadura perneras; //perneras
	int oro; //  gold

	std::string nombre; // nombre
	int nivel; //nivel
	int exp;
	int expSub; //expSub

	int fuerza; //fuerza
	int vitalidad; //vitalidad
	int reflejos; //reflejos
	int inteligencia; //inteligencia

	int vida; //vida
	int vidaMax; //vidaMax
	int energia; //energy
	int energiaMax; //energyMax
	int danoMin; //danoMin
	int danoMax; //danoMax
	int defensa; //defensa
	int presicion; //presicion
	int suerte; //suerte

	int estadisticasPts; //estadisticasPts

public:
	Personaje();
	Personaje(string nombre, int distanciaViajada,
		int oro, int nivel,
		int exp, int fuerza, int vitalidad,
		int reflejos, int inteligencia,
		int vida, int energia, int estadisticasPts);
	virtual ~Personaje();

	//Functions
	void init(const std::string nombre);//inialize
	void display() const; //display
	string getAsString()const; //getAsString
	string getInvAsString(bool tienda = false); //getInvAsString
	string getInvAsStringSave(); //getInvAsStringSave
	void subidaNvl();//subidaNvl
	void nuevStats();//nuevStats
	void addStats(int stat, int val);//addStats
	void equiparItem(unsigned index);//equiparItem
	inline void resetvida() { this->vida = this->vidaMax; }//resetvida
	void addItem(const Item &item) { this->inventario.addItem(item); } //addItem
	void removeItem(const int index);//removeItem
	const Item& getItem(const int index);//getItem

	//Accessors
	inline const int& getDistViajada() const { return this->distanciaViajada; }//getDistTravel
	inline const std::string& getNombre() const { return this->nombre; }//getnombre
	inline const int& getNivel() const { return this->nivel; }//getnivel
	inline const int& getExp() const { return this->exp; }//getExp
	inline const int& getExpSub() const { return this->expSub; }//getexpSub
	inline const int& getEstadisticasPts() const { return this->estadisticasPts; }//getestadisticasPts
	inline const int& getVida() const { return this->vida; }//getvida
	inline const int& getVidaMax() const { return this->vidaMax; }//getvidaMax
	inline const bool estaVivo() { return this->vida > 0; }//estaVivo
	inline const int& getenergia() const { return this->energia; }//getenergia
	inline const int& getDanoMin() const { return this->danoMin; }//getdanoMin
	inline const int& getDanoMax() const { return this->danoMax; }//getdanoMax
	inline const int getDano()const { return rand() % (this->danoMax + this->armaaa.getdanoMax()) + (this->danoMin + this->armaaa.getdanoMin()); }//getDamage
	inline const int& getDefensa() const { return this->defensa; }//getdefensa
	inline const int getSumaDefensa()const { return this->guantes.getDefensa() + this->peto.getDefensa() + this->perneras.getDefensa() + this->casco.getDefensa(); }//getAddeddefensa
	inline const int& getPresicion() const { return this->presicion; }//getpresicion
	inline const int getOro() const { return this->oro; }//getGold
	inline const int getInventarioTamano()const { return this->inventario.size(); }//getInventarioTamano

	//Modifier
	inline void setDistViajada(const int& distancia) { this->distanciaViajada = distancia; }//setDistTravelled
	inline void jugar() { this->distanciaViajada++; }//travel
	inline void masExp(const int exp) { this->exp += exp; }//gainExp
	inline void masOro(const int oro) { this->oro += oro; }//gainGold
	inline void pagarOro(const int oro) { this->oro -= oro; }//payGold
	void tomaDano(const int dano);//tomaDano
	inline void setArma(Arma armaaa) { this->armaaa = armaaa; }//setarma
	inline void setCasco(Armadura casco) { this->casco = casco; }//setCasco
	inline void setPeto(Armadura peto) { this->peto = peto; }//setArmaduraPETO
	inline void setGuantes(Armadura guantes) { this->guantes = guantes; }//setArmaduraGUANTES
	inline void setPerneras(Armadura perneras) { this->perneras = perneras; }//setArmaduraPERNERAS
};
