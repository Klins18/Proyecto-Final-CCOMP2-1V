#pragma once

#include"STLINCLUDE.h"

#include"Event.h"


class Game
{
private:
	int choice;
	bool playing;

	//Character related
	int activarPersonaje; //activarPersonaje
	std::vector<Personaje> personajes; //personajes
	std::string filenombre; //filename

	//Enemies
	dArr<Enemy> enemigos; //enemies

public:
	Game();
	virtual ~Game();

	//Operators

	//Functions
    void BarraCarga(); //Barra de carga
	void imprimeAscii(int); //Imprime el personaje en txt
	void initGame(); //initGame
	void menuPrincipal(); //mainMenu
	void creaNuevoPersonaje(); //createNewCharacter
	void subeNivelPersonaje(); //subidaNvlCharacter
	void menuPersonaje();//characterMenu
	void guardaPersonajes();//savepersonajes
	void cargaPersonajes();//cargaPersonajes
	void seleccionaPersonaje();//selectCharacter
	void viaje();//travel
	void descansar();// rest

	//Accessors
	inline bool getPlaying() const { return this->playing; }

	//Modifiers
};