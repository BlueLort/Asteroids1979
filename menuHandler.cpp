#include "menuHandler.h"




menuHandler::menuHandler()
{
	system("title Asteroids 1979");
	SYSTEM = MENU;
	ShowConsoleCursor(0);//to hide visibility of the cursor
	board_length = 0;//height of the leaderboard
	leaderboardLogic();//TO PREPARE SCORE IF PLAYER WANT TO SEE IT and check if files exist
	esc = 0;// flag to check whether im still in the menu or i entered another one
	RUNNING = 1;
	inGame = 0;
	CHOOSEN = 1;//to scroll through main menu
	buffer = '\0';//making sure initial buffer is empty not having garbage

	LOADED = 0;
}

void menuHandler::startGame()
{
	GAMESystem game;
	game.Game_Loop();
	game.~GAMESystem();
}

void menuHandler::menuEventHandler()
{
	switch (SYSTEM)
	{
	case MENU:
		ShowConsoleCursor(0);///IF USER RESIZE IT THEN IT WILL BE RESET
		CHOOSEN = 1;
		esc = 0;
		system("mode 80,25");
		system("cls");
		while (!esc)
		{

			setColor(11);
			gotoxy(1, 0);
			printf("Developed by Omar Nasr(lort)");
			setColor(12);
			gotoxy(1, 1);
			printf("**Up/Down -Enter To choose**");

			for (i = 1; i < 6; i++)
			{
				if (i == CHOOSEN) setColor(15);
				else setColor(8);
				switch (i)
				{
				case 1:
					gotoxy(1, i + 1);
					printf("Start");
					break;
				case 2:
					gotoxy(1, i + 1);
					printf("Load Game");
					break;
				case 3:
					gotoxy(1, i + 1);
					printf("Leaderboard");
					break;
				case 4:
					gotoxy(1, i + 1);
					printf("Options");
					break;
				case 5:
					gotoxy(1, i + 1);
					printf("Exit");
					break;
				}
			}

			buffer = _getch();
			if (buffer == (char)13)
			{
				switch (CHOOSEN)
				{
				case 1:
					SYSTEM = GAME;
					esc = 1;
					break;
				case 2:
					SYSTEM = OPTIONS;
					esc = 1;
					break;
				case 3:
					SYSTEM = EXIT;
					esc = 1;
					break;

				}
			}
			menuLogic();

		}
		break;
	case OPTIONS:
		CHOOSEN = 0;
		system("CLS");
		setColor(7);
		esc = 0;
		while (!esc)
		{
			setColor(12);
			gotoxy(1, 0);
			printf("**up/down &left/right to change setting(ESC to back)**");
			for (i = 0; i < 3; i++)
			{
				if (i == CHOOSEN) setColor(15);
				else setColor(8);
				switch (i)
				{
				case 0:
					gotoxy(1, i + 1);
					printf("Level:%.02d", GAMESystem::currentLevel);
					break;
				}
			}
			buffer = _getch();
			optionsLogic();


		}
		break;
	case GAME:
		startGame();
	
		break;
	case EXIT:
		RUNNING = 0;
		esc = 1;
		break;
	}
}

void menuHandler::menuLogic()
{
	switch (buffer)
	{
	case (char)224:
		buffer = _getch();
		if (buffer == (char)72) {
			if (CHOOSEN > 1)CHOOSEN--;
		}
		else if (buffer == (char)80) {
			if (CHOOSEN < 3)CHOOSEN++;
		}
		break;
	case (char)27:
		SYSTEM = EXIT;
		esc = 1;
		break;
	}
}

void menuHandler::optionsLogic()
{
	switch (buffer)
	{
	case (char)224:
		buffer = _getch();
		if (buffer == (char)72) {
			if (CHOOSEN > 0)CHOOSEN--;
		}
		else if (buffer == (char)80) {
			if (CHOOSEN < 0 )CHOOSEN++;
		}
		else  if (buffer == (char)75) {
			switch (CHOOSEN)
			{
			case 0:
				if (GAMESystem::currentLevel>1)GAMESystem::currentLevel -= 1;
				break;
			default:
				break;
			}
		}
		else if (buffer == (char)77) {
			switch (CHOOSEN)
			{
			case 0:
				if (GAMESystem::currentLevel <99)GAMESystem::currentLevel += 1;
				break;
			default:
				break;
			}
		}
		break;
	case (char)27:
		SYSTEM = MENU;
		esc = 1;
		break;
	}
}

void menuHandler::leaderboardLogic()
{
}

void menuHandler::emptyName(char * str, int n)
{
}


menuHandler::~menuHandler()
{
}
void menuHandler::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void menuHandler::ShowConsoleCursor(int showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void menuHandler::setColor(int i)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
