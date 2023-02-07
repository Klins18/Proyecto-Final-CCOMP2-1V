#include "Game.h"
#include <windows.h>
Game::Game()
{
	choice = 0;
	playing = true;
	activarPersonaje = 0;
	filenombre = "personajes.txt";
}

Game::~Game()
{

}

//Functions
void Game::initGame()
{
	std::ifstream in;
	in.open("personajes.txt");

	Arma::initnombres(); //
	Armadura::initnombres();

	if (in.is_open())
		this->cargaPersonajes();
	else
	{
		creaNuevoPersonaje(); //createNewCharacter
		this->guardaPersonajes(); //savepersonajes
	}

	in.close();	
}
void Game::BarraCarga(){
	int segundos = 1;
	std::cout << "\t\t\t\t   CARGANDO...\n";
	for(int i=0; i<90;i++){
        std::cout << char(219);
        Sleep(segundos*100/80);
    }
    std::cout<<"\nCompletado!\n";
}


void Game::imprimeAscii(int k){
	std::ifstream txtAscii;
	switch (k){
	case 0:
		txtAscii.open("/personajesASCII/persoAscii.txt");
		if(txtAscii.is_open()){
			std::string linea;
			while(std::getline(txtAscii, linea)){
				std::cout << linea << std::endl;
		}
		txtAscii.close();
		}
		break;
	case 1:
		std::cout << "  _______ _                 _            __                   _             _             \n"
			" |__   __| |               | |          / _|                 | |           (_)            \n"
			"    | |  | |__   __ _ _ __ | | _____   | |_ ___  _ __   _ __ | | __ _ _   _ _ _ __   __ _ \n"
			"    | |  | '_ \\ / _` | '_ \\| |/ / __|  |  _/ _ \\| '__| | '_ \\| |/ _` | | | | | '_ \\ / _` |\n"
			"    | |  | | | | (_| | | | |   <\\__ \\  | || (_) | |    | |_) | | (_| | |_| | | | | | (_| |\n"
			"    |_|  |_| |_|\\__,_|_| |_|_|\\_\\___/  |_| \\___/|_|    | .__/|_|\\__,_|\\__, |_|_| |_|\\__, |\n"
			"                                                       | |             __/ |         __/ |\n"
			"                                                       |_|            |___/         |___/ \n";
		break;
	case 2: //STATS
		txtAscii.open("/personajesASCII/stats.txt");
		if(txtAscii.is_open()){
			std::string linea;
			while(std::getline(txtAscii, linea)){
				std::cout << linea << std::endl;
		}
		txtAscii.close();
		}
		break;
	case 3: //MENU
		txtAscii.open("/personajesASCII/menu.txt");
		if(txtAscii.is_open()){
			std::string linea;
			while(std::getline(txtAscii, linea)){
				std::cout << linea << std::endl;
		}
		txtAscii.close();
		}
		break;			
	default:
		break;
	}
	
}

void Game::menuPrincipal()//mainMenu
{
	std::cout << "ENTER para continuar..." << "\n";
	std::cin.get();
	system("CLS");

	if (this->personajes[activarPersonaje].estaVivo()) //activarPersonaje,estaVivo
	{
		if (this->personajes[activarPersonaje].getExp() >=
			this->personajes[activarPersonaje].getExpSub())
		{
			std::cout << "SUBIDA DE NIVEL DISPONIBLE! \n\n"; //new nivel available
		}

		imprimeAscii(3);

		std::cout << "= Perfil Seleccionado: " <<
			this->personajes[activarPersonaje].getNombre() << " Nr: " << //personajes, activarPersonaje
			this->activarPersonaje + 1 << "/" << this->personajes.size() << //activarPersonaje, personajes
			" =" << "\n" << "\n";

		std::cout << "0: Salir" << "\n";
		std::cout << "1: Viajar" << "\n"; 
		std::cout << "2: Subir de nivel" << "\n"; 
		std::cout << "3: Descansar" << "\n"; 
		std::cout << "4: Hoja de personaje" << "\n"; 
		std::cout << "5: Crea nuevo personaje" << "\n"; 
		std::cout << "6: Selecciona personaje" << "\n"; 
		std::cout << "7: Guarda personajes" << "\n";
		std::cout << "8: Carga personajes" << "\n";

		std::cout << "\n";

		std::cout << "\n" << "Eleccion: ";
		std::cin >> this->choice;

		while (std::cin.fail() || this->choice > 9)
		{
			std::cout << "Entrada erronea!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "\n" << "Eleccion (0 - 8): "; 
			std::cin >> this->choice;
		}

		std::cin.ignore(100, '\n');
		std::cout << "\n";

		switch (this->choice)
		{
		case 0: //QUIT
			playing = false;
			this->guardaPersonajes(); 
			imprimeAscii(1);
			break;

		case 1:
			viaje();

			break;

		case 2: 
			this->subeNivelPersonaje();

			break;

		case 3: 
			descansar();

			break;

		case 4: 
			this->menuPersonaje(); 
			break;

		case 5: 
			creaNuevoPersonaje(); 
			guardaPersonajes(); 
			break;

		case 6: 
			seleccionaPersonaje();
			break;

		case 7: 
			guardaPersonajes();
			break;

		case 8: //LOAD CHARS
			cargaPersonajes();
			break;

		default:
			break;
		}
	}
	else
	{
		std::cout << "= ESTAS MUERTO, CARGAR? =" << "\n" << "\n";
		std::cout << "(0) SI, (1) NO " << "\n";
		std::cin >> this->choice;

		while (std::cin.fail() || this->choice < 0 || this->choice > 1)
		{
			std::cout << "Entrada erronea!" << "\n"; //Faulty input
			std::cin.clear();
			std::cin.ignore(100, '\n');
			
			std::cout << "(0) SI , (1) NO " << "\n";
			std::cin >> this->choice;
		}

		std::cin.ignore(100, '\n');
		std::cout << "\n";

		if (this->choice == 0)
			this->cargaPersonajes(); //cargaPersonajes
		else
			playing = false;
	}
}

void Game::creaNuevoPersonaje() //createNewCharacter
{
	std::string nombre = "";
	std::cout << "Nombre del personaje: "; //Character nombre
	std::getline(std::cin, nombre);

	for (size_t i = 0; i < this->personajes.size(); i++) //personajes
	{
		while (nombre == this->personajes[i].getNombre()) //personajes
		{
			std::cout << "Error! Personaje ya existente!" << "\n";
			std::cout << "Nombre del personaje: ";
			std::getline(std::cin, nombre);
		}
	}

	personajes.push_back(Personaje()); //personajes
	activarPersonaje= personajes.size() - 1; //activarPersonaje, personajes
	personajes[activarPersonaje].init(nombre); //personajes, activarPersonaje
}

void Game::subeNivelPersonaje() //subidaNvlCharacter
{
	this->personajes[activarPersonaje].subidaNvl();

	if (this->personajes[activarPersonaje].getEstadisticasPts() > 0)
	{
		std::cout << "Tienes puntos de estadistica que asignar!" << "\n\n";
		std::cout << "Estadistica a mejorar: " << "\n";
		std::cout << "0: fuerza " << "\n";
		std::cout << "1: vitalidad " << "\n";
		std::cout << "2: reflejos " << "\n";
		std::cout << "3: inteligencia " << "\n";

		std::cin >> this->choice;

		while (std::cin.fail() || this->choice > 3)
		{
			std::cout << "Entrada erronea!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "Estadistica a mejorar: " << "\n";
			std::cin >> this->choice;
		}

		std::cin.ignore(100, '\n');
		std::cout << "\n";

		switch (this->choice)
		{
		case 0: //fuerza
			this->personajes[activarPersonaje].addStats(0, 1);
			break;

		case 1://vitalidad
			this->personajes[activarPersonaje].addStats(1, 1);
			break;

		case 2://reflejos
			this->personajes[activarPersonaje].addStats(2, 1);
			break;

		case 3://inteligencia
			this->personajes[activarPersonaje].addStats(3, 1);
			break;

		default:

			break;
		}
	}
}

void Game::menuPersonaje()
{
	do
	{
		system("CLS");
		imprimeAscii(2);
		std::cout << gui::menu_title("MENU DEL PERSONAJE");

		std::cout << gui::menu_divider();

		personajes[activarPersonaje].display();

		std::cout << gui::menu_divider();

		std::cout << "= MENU =" << "\n";
		std::cout << gui::menu_item(0, "Mochila"); //Back
		std::cout << gui::menu_item(1, "Mostrar inventario"); //print inventario
		std::cout << gui::menu_item(2, "Equipar item"); //Equip Item
		std::cout << "\n";
		std::cout << "Eleccion: ";

		std::cin >> this->choice;

		while (std::cin.fail() || this->choice < 0 || this->choice > 2)
		{
			std::cout << "Entrada erronea!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "= MENU =" << "\n";
			std::cout << "0: Mochila" << "\n";
			std::cout << "1: Mostrar inventario" << "\n";
			std::cout << "2: Equipar Item" << "\n";
			std::cout << "\n";
			std::cout << "Eleccion: ";
			std::cin >> this->choice;
		}

		std::cin.ignore(100, '\n');
		std::cout << "\n";

		switch (this->choice)
		{
		case 1:
			std::cout << this->personajes[this->activarPersonaje].getInvAsString();

			break;

		case 2:
			std::cout << this->personajes[this->activarPersonaje].getInvAsString();
			
			std::cout << "Item index: ";
			std::cin >> this->choice;

			while (std::cin.fail() || this->choice < 0 || this->choice >= this->personajes[this->activarPersonaje].getInventarioTamano())
			{
				std::cout << "Entrada erronea!" << "\n";
				std::cin.clear();
				std::cin.ignore(100, '\n');

				std::cout << "Item index: ";
				std::cin >> this->choice;
			}

			std::cin.ignore(100, '\n');
			std::cout << "\n";
			
			this->personajes[this->activarPersonaje].equiparItem(this->choice);

			break;
		default:
			break;
		}

		if (this->choice > 0)
		{
			std::cout << "ENTER para continuar..." << "\n";
			std::cin.get();
		}
	
	} while (this->choice > 0);
}

void Game::guardaPersonajes()
{
	std::ofstream outFile(filenombre);

	if (outFile.is_open())
	{
		for (size_t i = 0; i < this->personajes.size(); i++)
		{
			outFile << this->personajes[i].getAsString() << "\n";
			outFile << this->personajes[i].getInvAsStringSave() << "\n";	
		}
	}

	outFile.close();
}

void Game::cargaPersonajes()
{
	std::ifstream inFile(filenombre);

	this->personajes.clear();

	std::string nombre = "";
	int distanceTravelled = 0;
	int gold = 0;
	int nivel = 0;
	int exp = 0;
	int fuerza = 0;
	int vitalidad = 0;
	int reflejos = 0;
	int inteligencia = 0;
	int vida = 0;
	int energia = 0;
	int statPoints = 0;

	//Item
	int itemtipo = 0;
	int defensa = 0;
	int tipo = 0;
	int danoMin = 0;
	int danoMax = 0;
	//nombre
	//nivel
	int buyval = 0;
	int sellval = 0;
	int rareza = 0;

	Inventario tempItems;

	std::string line = "";
	std::stringstream str;

	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			str.str(line);
			str >> nombre;	
			str >> distanceTravelled;
			str >> gold;
			str >> nivel;
			str >> exp;
			str >> fuerza;
			str >> vitalidad;
			str >> reflejos;
			str >> inteligencia;
			str >> vida;
			str >> energia;
			str >> statPoints;

			//Create characyer
			Personaje temp(nombre, distanceTravelled, gold, nivel,
				exp, fuerza, vitalidad, reflejos, inteligencia,
				vida, energia, statPoints);

			//Weapon
			str >>
				itemtipo >> nombre >> nivel >>
				rareza >> buyval >> sellval >>
				danoMin >> danoMax;

			Arma arma(danoMin, danoMax, nombre, nivel, buyval, sellval, rareza);	

			//Armadura CASCO
			str >>
				itemtipo >> nombre >> nivel >>
				rareza >> buyval >> sellval >>
				defensa >> tipo;

			Armadura Armadura_CASCO(tipo, defensa, nombre, nivel, buyval, sellval, rareza);

			//Armadura PETO
			str >>
				itemtipo >> nombre >> nivel >>
				rareza >> buyval >> sellval >>
				defensa >> tipo;

			Armadura Armadura_PETO(tipo, defensa, nombre, nivel, buyval, sellval, rareza);	

			//Armadura GUANTES
			str >>
				itemtipo >> nombre >> nivel >>
				rareza >> buyval >>sellval >>
				defensa >> tipo;

			Armadura Armadura_GUANTES(tipo, defensa, nombre, nivel, buyval, sellval, rareza);

			//Armadura PERNERAS
			str >>
				itemtipo >> nombre >> nivel >>
				rareza >> buyval >> sellval >>
				defensa >> tipo;

			Armadura Armadura_PERNERAS(tipo, defensa, nombre, nivel, buyval, sellval, rareza);

			temp.setArma(arma);
			temp.setCasco(Armadura_CASCO);
			temp.setPeto(Armadura_PETO);
			temp.setGuantes(Armadura_GUANTES);
			temp.setPerneras(Armadura_PERNERAS);

			//Add inventario Items
			str.clear();
			line.clear();
			getline(inFile, line);
			
			str.str(line);

			while (str >> 
				itemtipo >> nombre >> nivel >> 
				rareza >> buyval >> sellval >> 
				danoMin >> danoMax)
			{
				temp.addItem(
					Arma
					(
						danoMin,
						danoMax,
						nombre,
						nivel,
						buyval,
						sellval,
						rareza
					)
				);
			}

			str.clear();
			line.clear();
			getline(inFile, line);

			str.str(line);

			while (str >>
				itemtipo >> nombre >> nivel >>
				rareza >> buyval >> sellval >>
				defensa >> tipo)
			{
				temp.addItem(
					Armadura
					(
						tipo,
						defensa,
						nombre,
						nivel,
						buyval,
						sellval,
						rareza
					)
				);
			}

			this->personajes.push_back(Personaje(temp));

			std::cout << "Personaje " << temp.getNombre() << " cargado!\n";
		
			str.clear();
		}
	}

	inFile.close();

	if (this->personajes.size() <= 0)
	{
		throw "ERROR! Personajes no CARGADOS O ARCHIVO VACIO!";
	}
}

void Game::seleccionaPersonaje()
{
	std::cout << "Selecciona personaje: " << "\n\n";

	for (size_t i = 0; i < this->personajes.size(); i++)
	{
		std::cout << "Index: " << i << " = " << this->personajes[i].getNombre() << " nivel: " << this->personajes[i].getNivel() << "\n";
	}

	std::cout << "\n";

	std::cout << "Eleccion: ";

	std::cin >> this->choice;

	while (std::cin.fail() || this->choice >= this->personajes.size() || this->choice < 0)
	{
		std::cout << "Entrada erronea!" << "\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');

		std::cout << "Selecciona personaje: " << "\n";
		std::cin >> this->choice;
	}

	std::cin.ignore(100, '\n');
	std::cout << "\n";

	this->activarPersonaje = this->choice;

	std::cout << this->personajes[this->activarPersonaje].getNombre() << " is SELECTED!" << "\n\n";
}

void Game::viaje()
{
	this->personajes[activarPersonaje].jugar();

	Event ev;

	ev.generateEvent(this->personajes[activarPersonaje], this->enemigos);
}

void Game:: descansar()
{
	int restCost = this->personajes[this->activarPersonaje].getVidaMax() - this->personajes[this->activarPersonaje].getVida();
	std::cout << "= DESCANSAR =" << "\n\n";
	std::cout << "Descansar te cuesta: " << restCost << "\n";
	std::cout << "Tu oro: " << this->personajes[this->activarPersonaje].getOro() << "\n";
	std::cout << "vida: " << this->personajes[this->activarPersonaje].getVida() << " / " << this->personajes[this->activarPersonaje].getVidaMax() << "\n\n";

	if (this->personajes[this->activarPersonaje].getOro() < restCost)
	{
		std::cout << "Dinero insuficiente, lo sentimos!" << "\n\n";
	}
	else if (this->personajes[this->activarPersonaje].getVida() >= this->personajes[this->activarPersonaje].getVidaMax())
	{
		std::cout << "La vida ya esta llena!" << "\n\n";
	}
	else
	{
		std::cout << "\n\n Descansar? (0) Si, (1) No..." << "\n\n";

		std::cin >> this->choice;

		while (std::cin.fail() || this->choice < 0 || this->choice > 1)
		{
			std::cout << "Entrada erronea!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "\n\n Descansar? (0) Si, (1) No..." << "\n\n";
			std::cin >> this->choice;
		}

		std::cin.ignore(100, '\n');
		std::cout << "\n";

		if (this->choice == 0)
		{
			this->personajes[this->activarPersonaje].resetvida();
			this->personajes[this->activarPersonaje].pagarOro(restCost);
			std::cout << "DESCANSADO!" << "\n\n";
		}
		else
		{
			std::cout << "Quiza para la proxima!" << "\n\n";
		}
	}
}
