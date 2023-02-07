#include "Event.h"

int Event::nrOfEvents = 10;

Event::Event()
{
	
}

Event::~Event()
{

}

void Event::generateEvent(Personaje &character, dArr<Enemy>& enemies)
{
	int i = rand() % Event::nrOfEvents;

	switch (i)
	{
	case 0:
    case 1:
    case 2:
	case 3:
		//Enemy encounter
		this->enemyEncouter(character, enemies);
		break;
    case 4:
    case 5:
	case 6:
	case 7:
		//Puzzle
		this->puzzleEncouter(character);
		break;
    case 8:
		//tienda
		this->tiendaEncouter(character);
		break;
	case 9:
		//Boss
		std::cout << "Encuentro con Boss proximanente..." << "\n";
		break;

	default:
		break;
	}
}

//Different events
void Event::tiendaEncouter(Personaje&character)
{
	int choice = 0;
	bool tiendaping = true;
	Inventario merchantInv;
	std::string inv;
	
	//Init merchant inv
	int nrOfItems = rand() % 20 + 10;
	bool coinToss = false;

	for (size_t i = 0; i < nrOfItems; i++)
	{
		coinToss = rand() % 2;

		if(coinToss > 0)
			merchantInv.addItem(Arma(character.getNivel() + rand() % 5, rand() % 4));
		else
			merchantInv.addItem(Armadura(character.getNivel() + rand() % 5, rand() % 4));
	}

	while (tiendaping)
	{
		system("CLS");

		std::cout << "= tienda MENU =" << "\n\n";

		std::cout << "0: Salir de la Tienda" << "\n";
		std::cout << "1: Comprar" << "\n";
		std::cout << "2: Vender" << "\n";
		std::cout << "\n";

		std::cout << "Eleccion: ";

		std::cin >> choice;

		while (std::cin.fail() || choice > 3 || choice < 0)
		{
			system("CLS");

			std::cout << "Entrada Fallida!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "= tienda MENU =" << "\n\n";

			std::cout << "0: Salir de la tienda" << "\n";
			std::cout << "1: Comprar" << "\n";
			std::cout << "2: Vender" << "\n";

			std::cout << "\n";

			std::cout << "Choice: ";
			std::cin >> choice;
		}

		std::cin.ignore(100, '\n');
		std::cout << "\n";

		//tienda
		switch (choice)
		{
		case 0: //Leave
			tiendaping = false;
			break;

		case 1: //Buy

			std::cout << "= Menu Comprar =" << "\n\n";

			std::cout << " - ORO: " <<character.getOro() << "\n\n";

			inv.clear();

			for (size_t i = 0; i < merchantInv.size(); i++)
			{
				inv += std::to_string(i) + ": " + merchantInv[i].toString() + "\n - PRICE: " + std::to_string(merchantInv[i].getBuyval()) + "\n";
			}

			std::cout << inv << "\n";

			std::cout << "Oro: " << character.getOro() << "\n";
			std::cout << "Elije un articulo (-1 para salir): ";

			std::cin >> choice;

			while (std::cin.fail() || choice > merchantInv.size() || choice < -1)
			{
				system("CLS");

				std::cout << "Opcion invalida!" << "\n";
				std::cin.clear();
				std::cin.ignore(100, '\n');

				std::cout << "Oro: " << character.getOro() << "\n";
				std::cout << "Elije un articulo (-1 para salir): ";
				std::cin >> choice;
			}

			std::cin.ignore(100, '\n');
			std::cout << "\n";

			if (choice == -1)
			{
				std::cout << "Cancelado..." << "\n";
			}
			else if (character.getOro() >= merchantInv[choice].getBuyval())
			{
				character.pagarOro(merchantInv[choice].getBuyval());
				character.addItem(merchantInv[choice]);
				
				std::cout << "Item comprado." << merchantInv[choice].getnombre() << " -" << merchantInv[choice].getBuyval() << "\n";
				
				merchantInv.removeItem(choice);
			}
			else
			{
				std::cout << "No puedo permitirme este articulo!" << "\n";
			}

			break;

		case 2: //Sell

			std::cout << character.getInvAsString(true) << "\n";

			std::cout << "= MENU VENTA =" << "\n\n";

			std::cout << " - Oro: " << character.getOro() << "\n\n";

			if (character.getInventarioTamano() > 0)
			{
				std::cout << "Oro: " << character.getOro() << "\n";
				std::cout << "Elije un articulo (-1 para salir): ";

				std::cin >> choice;

				while (std::cin.fail() || choice > character.getInventarioTamano() || choice < -1)
				{
					system("CLS");

					std::cout << "Opcion invalida!" << "\n";
					std::cin.clear();
					std::cin.ignore(100, '\n');

					std::cout << "Oro: " << character.getOro() << "\n";
					std::cout << "Elije un articulo (-1 para salir): ";
					std::cin >> choice;
				}

				std::cin.ignore(100, '\n');
				std::cout << "\n";

				if (choice == -1)
				{
					std::cout << "Cancelado..." << "\n";
				}
				else
				{
					character.masOro(character.getItem(choice).getSellval());

					std::cout << "Item vendido!" << "\n";
					std::cout << "Oro obtenido: " << character.getItem(choice).getSellval() << "\n\n";
					character.removeItem(choice);
				}
			}
			else
			{
				std::cout << "inventario vacio..." << "\n";
			}

			break;

		default:
			break;
		}

		std::cout << "ENTER para continuar..." << "\n";
		std::cin.get();
	}

	std::cout << "Saliste de la tienda..." << "\n\n";
}

void Event::enemyEncouter(Personaje &character, dArr<Enemy>& enemies)
{
	bool playerTurn = false;
	int choice = 0;

	//Coin toss for turn
	int coinToss = rand() % 2 + 1;

	if (coinToss == 1)
		playerTurn = true;
	else
		playerTurn = false;

	//End conditions
	bool escape = false;
	bool playerDefeated = false;
	bool enemiesDefeated = false; 

	//Enemies
	int nrOfEnemies = rand() % 5 + 1;

	for (size_t i = 0; i < nrOfEnemies; i++)
	{
		enemies.push(Enemy(character.getNivel() + rand()%3));
	}

	//Battle variables
	int damage = 0;
	int gainExp = 0;
	int gainGold = 0;
	int playerTotal = 0;
	int enemyTotal = 0;
	int combatTotal = 0;
	int combatRollPlayer = 0;
	int combatRollEnemy = 0;

	while (!escape && !playerDefeated && !enemiesDefeated)
	{
		if (playerTurn && !playerDefeated)
		{
			//Menu
			//system("CLS");

			std::cout << "= TU TURNO =" << "\n\n";
			std::cout << "Continue..." << "\n\n";
			std::cin.get();
			system("CLS");

			std::cout << "= MENU DE BATALLA =" << "\n\n";
			std::cout << "vida: " << character.getVida() << " / " << character.getVidaMax() << "\n\n";

			std::cout << "0: Escape" << "\n";
			std::cout << "1: ATACAR" << "\n";
			std::cout << "2: DEFENDER" << "\n";
			std::cout << "3: USAR Item" << "\n";
			std::cout << "\n";

			std::cout << "Elige una opcion: ";

			std::cin >> choice;

			while (std::cin.fail() || choice > 3 || choice < 0)
			{
				system("CLS");

				std::cout << "Opcion invalida!" << "\n";
				std::cin.clear();
				std::cin.ignore(100, '\n');		

				std::cout << "= MENU DE BATALLA =" << "\n\n";

				std::cout << "0: Escape" << "\n";
				std::cout << "1: ATACAR" << "\n";
				std::cout << "2: DEFENDER" << "\n";
				std::cout << "3: USAR ITEM" << "\n";
				std::cout << "\n";

				std::cout << "Elige una opcion: ";
				std::cin >> choice;
			}

			std::cin.ignore(100, '\n');
			std::cout << "\n";

			//Moves
			switch (choice)
			{
			case 0: //ESCAPE
				escape = true;
				break;

			case 1: //ATTACK

				//Seleccionar Enemigo
				std::cout << "Seleccionar Enemigo: " << "\n\n";

				for (size_t i = 0; i < enemies.size(); i++)
				{
					std::cout << i << ": "
						<< "nivel: " << enemies[i].getnivel() << " - " <<
						"vida: " << enemies[i].getvida() << "/" << enemies[i].getvidaMax() << " - " <<
						"defensa: " << enemies[i].getdefensa() << " - " <<
						"presicion: " << enemies[i].getpresicion() << " - " <<
						"Daño: " << enemies[i].getdanoMin() << " - " << enemies[i].getdanoMax() <<
						"\n";
				}

				std::cout << "\n";
				std::cout << "Elige una opcion: ";

				std::cin >> choice;

				while (std::cin.fail() || choice >= enemies.size() || choice < 0)
				{
					std::cout << "Opcion invalida!" << "\n";
					std::cin.clear();
					std::cin.ignore(100, '\n');

					std::cout << "Seleccionar Enemigo: " << "\n\n";
					std::cout << "Elige una opcion: ";
					std::cin >> choice;
				}

				std::cin.ignore(100, '\n');
				std::cout << "\n";

				//Attack roll
				combatTotal = enemies[choice].getdefensa() + character.getPresicion();
				enemyTotal = enemies[choice].getdefensa() / (double)combatTotal * 100;
				playerTotal = character.getPresicion() / (double)combatTotal * 100;
				combatRollPlayer = rand() % playerTotal + 1;
				combatRollEnemy = rand() % enemyTotal + 1;

				std::cout << "Total de Combates: " << combatTotal << "\n";
				std::cout << "Porcentaje Enemigo: " << enemyTotal << "\n";
				std::cout << "Porcentaje del Jugador: " << playerTotal << "\n\n";
				std::cout << "Jugador Roll: " << combatRollPlayer << "\n";
				std::cout << "Jugador Roll: " << combatRollEnemy << "\n\n";

				if (combatRollPlayer > combatRollEnemy) //Hit
				{
					std::cout << "HIT! " << "\n\n";
					
					damage = character.getDano();
					enemies[choice].tomaDano(damage);

					std::cout << "Danio: " << damage << "!" << "\n\n";

					if (!enemies[choice].estaVivo())
					{
						std::cout << "ENEMIGO DERROTADO!" << "\n\n";
						gainExp = enemies[choice].getExp();
						character.masExp(gainExp);
						gainGold = rand() % enemies[choice].getnivel() * 10 + 1;
						character.masOro(gainGold);
						std::cout << "EXP GANADA: " << gainExp << "\n";
						std::cout << "ORO GANADO: " << gainGold << "\n\n";

						//Item roll
						int roll = rand() % 100 + 1;
						int rareza = -1;

						if (roll > 20)
						{
							rareza = 0; //Common
							
							roll = rand() % 100 + 1;
							if (roll > 30)
							{
								rareza = 1; //Uncommon

								roll = rand() % 100 + 1;
								if (roll > 50)
								{
									rareza = 2; //Rare

									roll = rand() % 100 + 1;
									if (roll > 70)
									{
										rareza = 3; //Legendary

										roll = rand() % 100 + 1;
										if (roll > 90)
										{
											rareza = 4; //Mythic
										}
									}
								}
							}
						}

						if (roll >= 0)
						{
							roll = rand() % 100 + 1;

							if (roll > 50)
							{
								Arma tempW(character.getNivel(), rareza);
								character.addItem(tempW);
								std::cout << "ARMA CAIDA!" << "\n";
							}
							else
							{
								Armadura tempA(character.getNivel(), rareza);
								character.addItem(tempA);
								std::cout << "ARMADURA CAIDA!" << "\n";
							}
						}

 						enemies.remove(choice);
					}
				}
				else //Miss
				{
					std::cout << "MISSED! \n\n";
				}

				break;

			case 2: //DEFEND

				break;

			case 3: //ITEM

				break;

			default:
				break;
			}

			//Final del turno
			playerTurn = false;
		}
		else if(!playerTurn && !playerDefeated && !escape && !enemiesDefeated)
		{
			std::cout << "= TURNO ENEMIGO =" << "\n";

			std::cout << "Continue..." << "\n\n";		
			std::cin.get();
			system("CLS");

			//Enemy attack
			for (size_t i = 0; i < enemies.size(); i++)
			{
				std::cout << "Continue..." << "\n\n";
				std::cin.get();
				system("CLS");
				
				std::cout << "Enemigo: " << i << "\n\n";

				//Attack roll
				combatTotal = enemies[i].getpresicion() + (character.getDefensa() + character.getSumaDefensa());
				enemyTotal = enemies[i].getpresicion() / (double)combatTotal * 100;
				playerTotal = (character.getDefensa() + character.getSumaDefensa()) / (double)combatTotal * 100;
				combatRollPlayer = rand() % playerTotal + 1;
				combatRollEnemy = rand() % enemyTotal + 1;

				std::cout << "Total de Combates: " << combatTotal << "\n";
				std::cout << "Porcentaje Enemigo: " << enemyTotal << "\n";
				std::cout << "Porcentaje del Jugador: " << playerTotal << "\n\n";
				std::cout << "Jugador Roll: " << combatRollPlayer << "\n";
				std::cout << "Jugador Roll: " << combatRollEnemy << "\n\n";

				if (combatRollPlayer < combatRollEnemy) //Hit
				{
					std::cout << "HIT! " << "\n\n";

					damage = enemies[i].getDamage();
					character.tomaDano(damage);

					std::cout << "Danio: " << damage << "!" << "\n";
					std::cout << "vida: " << character.getVida() << " / " << character.getVidaMax() << "\n\n";

					if (!character.estaVivo())
					{
						std::cout << "HAS SIDO DERROTADO!" << "\n\n";
						playerDefeated = true;
					}
				}
				else //Miss
				{
					std::cout << "MISSED! \n\n";
				}
			}

			//End turn
			playerTurn = true;
		}

		//Conditions
		if (!character.estaVivo())
		{
			playerDefeated = true;
		}
		else if (enemies.size() <= 0)
		{
			enemiesDefeated = true;
		}
	}
}

void Event::puzzleEncouter(Personaje &character)
{
	bool completed = false;
	int userAns = 0;
	int chances = 2;
	int gainExp = (chances * character.getNivel() * (rand()%10 + 1));
	int gainGold = (chances * character.getNivel() * (rand() % 10 + 1));

	int puzzleSelection = rand() % 2;
	std::string puzzleFile = "Puzzles/";
	if (puzzleSelection == 0){
		puzzleFile += "1.txt";
	}
	else{
		puzzleFile += "2.txt";
	}
	Puzzle puzzle(puzzleFile);

	while (!completed && chances > 0){
		std::cout << "OPORTUNIDADES: " << chances << "\n\n";
		chances--;
		std::cout << puzzle.getAsString() << "\n";

		std::cout << "\nTU RESPUESTA: ";
		std::cin >> userAns;

		while (std::cin.fail())
		{
			std::cout << "Opcion invalida!" << "\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');

			std::cout << "\nTU RESPUESTA: ";
			std::cin >> userAns;				
		}
		
		std::cin.ignore(100, '\n');
		std::cout << "\n";

		if (puzzle.getCorrectAns() == userAns)
		{
			completed = true;

			character.masExp(gainExp);
			character.masExp(gainGold);
			std::cout << "GANAS " << gainExp << " EXP!" << "\n";
			std::cout << "GANAS " << gainGold << " ORO!" << "\n\n";
		}
	}

	if (completed)
	{
		std::cout << "FELICIDADES LO CONSEGUISTE! \n\n";
	}
	else
	{
		std::cout << "FALLASTE!! \n\n";
	}
}

void Event::bossEncouter(Personaje& character, Boss& boss)
{}