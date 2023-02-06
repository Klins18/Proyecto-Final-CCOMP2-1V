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
	ifstream in;
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
	int segundos = 2;
	std::cout << "\t\t\t\t   CARGANDO...\n";
	for(int i=0; i<90;i++){
        std::cout << char(219);
        Sleep(segundos*1000/80);
    }
    std::cout<<"\nCompletado!\n";
}
void Game::menuPrincipal()//mainMenu
{
	cout << "ENTER para continuar..." << "\n";
	cin.get();
	system("CLS");

	if (this->personajes[activarPersonaje].estaVivo()) //activarPersonaje,estaVivo
	{
		if (this->personajes[activarPersonaje].getExp() >=
			this->personajes[activarPersonaje].getExpSub())
		{
			cout << "SUBIDA DE NIVEL DISPONIBLE! \n\n"; //new nivel available
		}

		cout << "= MENU PRINCIPAL =" << "\n" << "\n"; //main menu

		cout << "= Active character: " <<
			this->personajes[activarPersonaje].getNombre() << " Nr: " << //personajes, activarPersonaje
			this->activarPersonaje + 1 << "/" << this->personajes.size() << //activarPersonaje, personajes
			" =" << "\n" << "\n";

		cout << "0: Salir" << "\n"; //Quit
		cout << "1: Viajar" << "\n"; //Travel
		cout << "2: Subir de nivel" << "\n"; //nivel up
		cout << "3: Descansar" << "\n"; //rest
		cout << "4: Hoja de personaje" << "\n"; //Character sheet
		cout << "5: Crea nuevo personaje" << "\n"; //Create new character
		cout << "6: Selecciona personaje" << "\n"; //Select character
		cout << "7: Guarda personajes" << "\n"; //Save personajes
		cout << "8: Carga personajes" << "\n"; //Load personajes

		cout << "\n";

		cout << "\n" << "Eleccion: "; //Choice
		cin >> this->choice;

		while (cin.fail() || this->choice > 9)
		{
			cout << "Entrada erronea!" << "\n";//Faulty input
			cin.clear();
			cin.ignore(100, '\n');

			cout << "\n" << "Eleccion (0 - 8): "; // choice
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		switch (this->choice)
		{
		case 0: //QUIT
			playing = false;
			this->guardaPersonajes(); //savepersonajes
			
		std::cout << "  _______ _                 _            __                   _             _             \n"
			" |__   __| |               | |          / _|                 | |           (_)            \n"
			"    | |  | |__   __ _ _ __ | | _____   | |_ ___  _ __   _ __ | | __ _ _   _ _ _ __   __ _ \n"
			"    | |  | '_ \\ / _` | '_ \\| |/ / __|  |  _/ _ \\| '__| | '_ \\| |/ _` | | | | | '_ \\ / _` |\n"
			"    | |  | | | | (_| | | | |   <\\__ \\  | || (_) | |    | |_) | | (_| | |_| | | | | | (_| |\n"
			"    |_|  |_| |_|\\__,_|_| |_|_|\\_\\___/  |_| \\___/|_|    | .__/|_|\\__,_|\\__, |_|_| |_|\\__, |\n"
			"                                                       | |             __/ |         __/ |\n"
			"                                                       |_|            |___/         |___/ \n";
			break;

		case 1: //TRAVEL
			viaje();

			break;

		case 2: //nivel UP
			this->subeNivelPersonaje();

			break;

		case 3: //REST
			descansar();

			break;

		case 4: //CHAR SHEET
			this->menuPersonaje(); //characterMenu
			break;

		case 5: //CREATE NEW CHAR
			creaNuevoPersonaje(); //createNewCharacter
			guardaPersonajes(); //savepersonajes
			break;

		case 6: //SELECT CHAR
			seleccionaPersonaje(); //selectCharacter
			break;

		case 7: //SAVE CHARS
			guardaPersonajes(); //savepersonajes
			break;

		case 8: //LOAD CHARS
			cargaPersonajes(); //cargaPersonajes
			break;

		default:
			break;
		}
	}
	else
	{
		cout << "= ESTAS MUERTO, CARGAR? =" << "\n" << "\n";
		cout << "(0) SI, (1) NO " << "\n";
		cin >> this->choice;

		while (cin.fail() || this->choice < 0 || this->choice > 1)
		{
			cout << "Entrada erronea!" << "\n"; //Faulty input
			cin.clear();
			cin.ignore(100, '\n');
			
			cout << "(0) SI , (1) NO " << "\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		if (this->choice == 0)
			this->cargaPersonajes(); //cargaPersonajes
		else
			playing = false;
	}
}

void Game::creaNuevoPersonaje() //createNewCharacter
{
	string nombre = "";
	cout << "Nombre del personaje: "; //Character nombre
	getline(cin, nombre);

	for (size_t i = 0; i < this->personajes.size(); i++) //personajes
	{
		while (nombre == this->personajes[i].getNombre()) //personajes
		{
			cout << "Error! Personaje ya existente!" << "\n";
			cout << "Nombre del personaje: ";
			getline(cin, nombre);
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
		cout << "Tienes puntos de estadistica que asignar!" << "\n\n";
		cout << "Estadistica a mejorar: " << "\n";
		cout << "0: fuerza " << "\n";
		cout << "1: vitalidad " << "\n";
		cout << "2: reflejos " << "\n";
		cout << "3: inteligencia " << "\n";

		cin >> this->choice;

		while (cin.fail() || this->choice > 3)
		{
			cout << "Entrada erronea!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "Estadistica a mejorar: " << "\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

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
		cout << gui::menu_title("MENU DEL PERSONAJE");

		cout << gui::menu_divider();

		personajes[activarPersonaje].display();

		cout << gui::menu_divider();

		cout << "= MENU =" << "\n";
		cout << gui::menu_item(0, "Mochila"); //Back
		cout << gui::menu_item(1, "Mostrar inventario"); //print inventario
		cout << gui::menu_item(2, "Equipar item"); //Equip Item
		cout << "\n";
		cout << "Eleccion: ";

		cin >> this->choice;

		while (cin.fail() || this->choice < 0 || this->choice > 2)
		{
			cout << "Entrada erronea!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "= MENU =" << "\n";
			cout << "0: Mochila" << "\n";
			cout << "1: Mostrar inventario" << "\n";
			cout << "2: Equipar Item" << "\n";
			cout << "\n";
			cout << "Eleccion: ";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		switch (this->choice)
		{
		case 1:
			cout << this->personajes[this->activarPersonaje].getInvAsString();

			break;

		case 2:
			cout << this->personajes[this->activarPersonaje].getInvAsString();
			
			cout << "Item index: ";
			cin >> this->choice;

			while (cin.fail() || this->choice < 0 || this->choice >= this->personajes[this->activarPersonaje].getInventarioTamano())
			{
				cout << "Entrada erronea!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');

				cout << "Item index: ";
				cin >> this->choice;
			}

			cin.ignore(100, '\n');
			cout << "\n";
			
			this->personajes[this->activarPersonaje].equiparItem(this->choice);

			break;
		default:
			break;
		}

		if (this->choice > 0)
		{
			cout << "ENTER para continuar..." << "\n";
			cin.get();
		}
	
	} while (this->choice > 0);
}

void Game::guardaPersonajes()
{
	ofstream outFile(filenombre);

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
	ifstream inFile(filenombre);

	this->personajes.clear();

	string nombre = "";
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

	string line = "";
	stringstream str;

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

			cout << "Personaje " << temp.getNombre() << " cargado!\n";
		
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
	cout << "Selecciona personaje: " << "\n\n";

	for (size_t i = 0; i < this->personajes.size(); i++)
	{
		cout << "Index: " << i << " = " << this->personajes[i].getNombre() << " nivel: " << this->personajes[i].getNivel() << "\n";
	}

	cout << "\n";

	cout << "Eleccion: ";

	cin >> this->choice;

	while (cin.fail() || this->choice >= this->personajes.size() || this->choice < 0)
	{
		cout << "Entrada erronea!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');

		cout << "Selecciona personaje: " << "\n";
		cin >> this->choice;
	}

	cin.ignore(100, '\n');
	cout << "\n";

	this->activarPersonaje = this->choice;

	cout << this->personajes[this->activarPersonaje].getNombre() << " is SELECTED!" << "\n\n";
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
	cout << "= DESCANSAR =" << "\n\n";
	cout << "Descansar te cuesta: " << restCost << "\n";
	cout << "Tu oro: " << this->personajes[this->activarPersonaje].getOro() << "\n";
	cout << "vida: " << this->personajes[this->activarPersonaje].getVida() << " / " << this->personajes[this->activarPersonaje].getVidaMax() << "\n\n";

	if (this->personajes[this->activarPersonaje].getOro() < restCost)
	{
		cout << "Dinero insuficiente, lo sentimos!" << "\n\n";
	}
	else if (this->personajes[this->activarPersonaje].getVida() >= this->personajes[this->activarPersonaje].getVidaMax())
	{
		cout << "La vida ya esta llena!" << "\n\n";
	}
	else
	{
		cout << "\n\n Descansar? (0) Si, (1) No..." << "\n\n";

		cin >> this->choice;

		while (cin.fail() || this->choice < 0 || this->choice > 1)
		{
			cout << "Entrada erronea!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "\n\n Descansar? (0) Si, (1) No..." << "\n\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		if (this->choice == 0)
		{
			this->personajes[this->activarPersonaje].resetvida();
			this->personajes[this->activarPersonaje].pagarOro(restCost);
			cout << "DESCANSADO!" << "\n\n";
		}
		else
		{
			cout << "Quiza para la proxima!" << "\n\n";
		}
	}
}
