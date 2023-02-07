#include "Event.h"

int Event::nrOfEvents = 10;

using namespace std;;

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
		cout << "Encuentro con Boss proximanente..." << "\n";
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
	string inv;
	
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

		cout << "= tienda MENU =" << "\n\n";

		cout << "0: Leave" << "\n";
		cout << "1: Buy" << "\n";
		cout << "2: Sell" << "\n";
		cout << "\n";

		cout << "Choice: ";

		cin >> choice;

		while (cin.fail() || choice > 3 || choice < 0)
		{
			system("CLS");

			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "= tienda MENU =" << "\n\n";

			cout << "0: Leave" << "\n";
			cout << "1: Buy" << "\n";
			cout << "2: Sell" << "\n";

			cout << "\n";

			cout << "Choice: ";
			cin >> choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		//tienda
		switch (choice)
		{
		case 0: //Leave
			tiendaping = false;
			break;

		case 1: //Buy

			cout << "= BUY MENU =" << "\n\n";

			cout << " - Gold: " <<character.getOro() << "\n\n";

			inv.clear();

			for (size_t i = 0; i < merchantInv.size(); i++)
			{
				inv += to_string(i) + ": " + merchantInv[i].toString() + "\n - PRICE: " + to_string(merchantInv[i].getBuyval()) + "\n";
			}

			cout << inv << "\n";

			cout << "Gold: " << character.getOro() << "\n";
			cout << "Choice of item (-1 to cancel): ";

			cin >> choice;

			while (cin.fail() || choice > merchantInv.size() || choice < -1)
			{
				system("CLS");

				cout << "Faulty input!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');

				cout << "Gold: " << character.getOro() << "\n";
				cout << "Choice of item (-1 to cancel): ";
				cin >> choice;
			}

			cin.ignore(100, '\n');
			cout << "\n";

			if (choice == -1)
			{
				cout << "Cancelled..." << "\n";
			}
			else if (character.getOro() >= merchantInv[choice].getBuyval())
			{
				character.pagarOro(merchantInv[choice].getBuyval());
				character.addItem(merchantInv[choice]);
				
				cout << "Bought item " << merchantInv[choice].getnombre() << " -" << merchantInv[choice].getBuyval() << "\n";
				
				merchantInv.removeItem(choice);
			}
			else
			{
				cout << "Can't afford this item!" << "\n";
			}

			break;

		case 2: //Sell

			cout << character.getInvAsString(true) << "\n";

			cout << "= SELL MENU =" << "\n\n";

			cout << " - Gold: " << character.getOro() << "\n\n";

			if (character.getInventarioTamano() > 0)
			{
				cout << "Gold: " << character.getOro() << "\n";
				cout << "Choice of item (-1 to cancel): ";

				cin >> choice;

				while (cin.fail() || choice > character.getInventarioTamano() || choice < -1)
				{
					system("CLS");

					cout << "Faulty input!" << "\n";
					cin.clear();
					cin.ignore(100, '\n');

					cout << "Gold: " << character.getOro() << "\n";
					cout << "Choice of item (-1 to cancel): ";
					cin >> choice;
				}

				cin.ignore(100, '\n');
				cout << "\n";

				if (choice == -1)
				{
					cout << "Cancelled..." << "\n";
				}
				else
				{
					character.masOro(character.getItem(choice).getSellval());

					cout << "Item sold!" << "\n";
					cout << "Gold earned: " << character.getItem(choice).getSellval() << "\n\n";
					character.removeItem(choice);
				}
			}
			else
			{
				cout << "inventario empty..." << "\n";
			}

			break;

		default:
			break;
		}

		cout << "ENTER to continue..." << "\n";
		cin.get();
	}

	cout << "You left the tienda.." << "\n\n";
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

			cout << "= PLAYER TURN =" << "\n\n";
			cout << "Continue..." << "\n\n";
			cin.get();
			system("CLS");

			cout << "= BATTLE MENU =" << "\n\n";
			cout << "vida: " << character.getVida() << " / " << character.getVidaMax() << "\n\n";

			cout << "0: Escape" << "\n";
			cout << "1: Attack" << "\n";
			cout << "2: Defend" << "\n";
			cout << "3: Use Item" << "\n";
			cout << "\n";

			cout << "Choice: ";

			cin >> choice;

			while (cin.fail() || choice > 3 || choice < 0)
			{
				system("CLS");

				cout << "Faulty input!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');		

				cout << "= BATTLE MENU =" << "\n\n";

				cout << "0: Escape" << "\n";
				cout << "1: Attack" << "\n";
				cout << "2: Defend" << "\n";
				cout << "3: Use Item" << "\n";
				cout << "\n";

				cout << "Choice: ";
				cin >> choice;
			}

			cin.ignore(100, '\n');
			cout << "\n";

			//Moves
			switch (choice)
			{
			case 0: //ESCAPE
				escape = true;
				break;

			case 1: //ATTACK

				//Select enemy
				cout << "Select enemy: " << "\n\n";

				for (size_t i = 0; i < enemies.size(); i++)
				{
					cout << i << ": "
						<< "nivel: " << enemies[i].getnivel() << " - " <<
						"vida: " << enemies[i].getvida() << "/" << enemies[i].getvidaMax() << " - " <<
						"defensa: " << enemies[i].getdefensa() << " - " <<
						"presicion: " << enemies[i].getpresicion() << " - " <<
						"Damage: " << enemies[i].getdanoMin() << " - " << enemies[i].getdanoMax() <<
						"\n";
				}

				cout << "\n";
				cout << "Choice: ";

				cin >> choice;

				while (cin.fail() || choice >= enemies.size() || choice < 0)
				{
					cout << "Faulty input!" << "\n";
					cin.clear();
					cin.ignore(100, '\n');

					cout << "Select enemy: " << "\n\n";
					cout << "Choice: ";
					cin >> choice;
				}

				cin.ignore(100, '\n');
				cout << "\n";

				//Attack roll
				combatTotal = enemies[choice].getdefensa() + character.getPresicion();
				enemyTotal = enemies[choice].getdefensa() / (double)combatTotal * 100;
				playerTotal = character.getPresicion() / (double)combatTotal * 100;
				combatRollPlayer = rand() % playerTotal + 1;
				combatRollEnemy = rand() % enemyTotal + 1;

				cout << "Combat total: " << combatTotal << "\n";
				cout << "Enemy percent: " << enemyTotal << "\n";
				cout << "Player percent: " << playerTotal << "\n\n";
				cout << "Player roll: " << combatRollPlayer << "\n";
				cout << "Enemy roll: " << combatRollEnemy << "\n\n";

				if (combatRollPlayer > combatRollEnemy) //Hit
				{
					cout << "HIT! " << "\n\n";
					
					damage = character.getDano();
					enemies[choice].tomaDano(damage);

					cout << "Damage: " << damage << "!" << "\n\n";

					if (!enemies[choice].estaVivo())
					{
						cout << "ENEMY DEFEATED!" << "\n\n";
						gainExp = enemies[choice].getExp();
						character.masExp(gainExp);
						gainGold = rand() % enemies[choice].getnivel() * 10 + 1;
						character.masOro(gainGold);
						cout << "EXP GAINED: " << gainExp << "\n";
						cout << "GOLD GAINED: " << gainGold << "\n\n";

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
								cout << "arma DROP!" << "\n";
							}
							else
							{
								Armadura tempA(character.getNivel(), rareza);
								character.addItem(tempA);
								cout << "Armadura DROP!" << "\n";
							}
						}

 						enemies.remove(choice);
					}
				}
				else //Miss
				{
					cout << "MISSED! \n\n";
				}

				break;

			case 2: //DEFEND

				break;

			case 3: //ITEM

				break;

			default:
				break;
			}

			//End turn
			playerTurn = false;
		}
		else if(!playerTurn && !playerDefeated && !escape && !enemiesDefeated)
		{
			cout << "= ENEMY TURN =" << "\n";

			cout << "Continue..." << "\n\n";		
			cin.get();
			system("CLS");

			//Enemy attack
			for (size_t i = 0; i < enemies.size(); i++)
			{
				cout << "Continue..." << "\n\n";
				cin.get();
				system("CLS");
				
				cout << "Enemy: " << i << "\n\n";

				//Attack roll
				combatTotal = enemies[i].getpresicion() + (character.getDefensa() + character.getSumaDefensa());
				enemyTotal = enemies[i].getpresicion() / (double)combatTotal * 100;
				playerTotal = (character.getDefensa() + character.getSumaDefensa()) / (double)combatTotal * 100;
				combatRollPlayer = rand() % playerTotal + 1;
				combatRollEnemy = rand() % enemyTotal + 1;

				cout << "Combat total: " << combatTotal << "\n";
				cout << "Enemy percent: " << enemyTotal << "\n";
				cout << "Player percent: " << playerTotal << "\n\n";
				cout << "Player roll: " << combatRollPlayer << "\n";
				cout << "Enemy roll: " << combatRollEnemy << "\n\n";

				if (combatRollPlayer < combatRollEnemy) //Hit
				{
					cout << "HIT! " << "\n\n";

					damage = enemies[i].getDamage();
					character.tomaDano(damage);

					cout << "Damage: " << damage << "!" << "\n";
					cout << "vida: " << character.getVida() << " / " << character.getVidaMax() << "\n\n";

					if (!character.estaVivo())
					{
						cout << "YOU ARE DEFEATED!" << "\n\n";
						playerDefeated = true;
					}
				}
				else //Miss
				{
					cout << "MISSED! \n\n";
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
		std::cout << "Chances: " << chances << "\n\n";
		chances--;
		std::cout << puzzle.getAsString() << "\n";

		cout << "\nYour ANSWER: ";
		cin >> userAns;

		while (cin.fail())
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "\nYour ANSWER: ";
			cin >> userAns;				
		}
		
		cin.ignore(100, '\n');
		cout << "\n";

		if (puzzle.getCorrectAns() == userAns)
		{
			completed = true;

			character.masExp(gainExp);
			character.masExp(gainGold);
			std::cout << "YOU GAINED " << gainExp << " EXP!" << "\n";
			std::cout << "YOU GAINED " << gainGold << " GOLD!" << "\n\n";
		}
	}

	if (completed)
	{
		std::cout << "CONGRATZ YOU SUCCEDED! \n\n";
	}
	else
	{
		std::cout << "YOU FAILED BRAH! \n\n";
	}
}

void Event::bossEncouter(Personaje& character, Boss& boss)
{}