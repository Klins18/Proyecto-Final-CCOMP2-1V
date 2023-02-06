#include "Enemy.h"

Enemy::Enemy(int nivel)
{
	this->nivel = nivel;
	this->vidaMax = rand()% (nivel * 10) + (nivel * 2);
	this->vida = this->vidaMax;
	this->danoMin = this->nivel * 1;
	this->danoMax = this->nivel * 2;
	this->dropChance = rand() % 100 + 1;
	this->defensa = rand() % nivel*5 + 1;
	this->presicion = rand() % nivel*5 + 1;
}

Enemy::~Enemy()
{

}

std::string Enemy::getAsString()const
{
	return "nivel: " + std::to_string(this->nivel) + "\n" +
		"vida: " + std::to_string(this->vida) + " / " + std::to_string(this->vidaMax) + "\n" +
		"Damage: " + std::to_string(this->danoMin) + " - " + std::to_string(this->danoMax) + "\n" +
		"defensa: " + std::to_string(this->defensa) + "\n" +
		"presicion: " + std::to_string(this->presicion) + "\n" +
		"Drop chance: " + std::to_string(this->dropChance) + "\n";
}

void Enemy::tomaDano(int damage)
{
	this->vida -= damage; 

	if (this->vida <= 0)
	{
		this->vida = 0;
	}
}