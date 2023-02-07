#include"Game.h"

int main()
{
	srand(time(NULL));

	Game game;
	game.BarraCarga();
	game.imprimeAscii(0);
	game.initGame();
	
	while (game.getPlaying())
	{
		game.menuPrincipal();
	}

	return 0;
}