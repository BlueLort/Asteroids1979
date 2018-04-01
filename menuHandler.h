#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "GAMESystem.h"
class menuHandler
{
public:
	menuHandler();
	~menuHandler();
	void gotoxy(int x, int y);
	void ShowConsoleCursor(int showFlag);
	void setColor(int i);
	
	/*                      SYSTEM ENUMS                                 */
	enum gameState { MENU, OPTIONS, EXIT, GAME } SYSTEM;

	/*                      VARIABLES                                 */
	///SYSTEM VARIABLES
	int esc;// flag to check whether im still in the menu or i entered another one
	int RUNNING;//MAIN PROGRAM LOOP FLAG
	int inGame;//FLAG TO KNOW IF THE USER IN GAME OR NOT
	int i, j;//loop counters I KNOW ITS BAD TO PUT LOOP COUNTERS AS GLOBAL VARIABLES -> I'M SO LAZY xD
	char buffer; // to never lose clicked button on keyboard
	int LOADED;//flag to check if the game was loaded or not
	int CHOOSEN;//to scroll through main menu
	int board_length;//LEADERBOARD HEIGHT
	 /*                           FUNCTIONS                         */
	void startGame();
	///MENU HANDLING AND LOGIC
	 void menuEventHandler();//STARTS THE MAIN MENU AND ITS STUFF OF LOGIC
	 void menuLogic();//CHECK USER KEY PRESSES AND MOVES CURSOR TO CHOOSEN LINE
	 void optionsLogic();//SAME AS ABOVE BUT FOR OPTIONS
	 void leaderboardLogic();
	 void emptyName(char*str, int n);//EMPTIES A STRING GIVEN TO IT(by putting spaces)
};

