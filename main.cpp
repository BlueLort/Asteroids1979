/*
			DEVELOPED BY Omar Nasr(Lort)
			email:emaranasr@gmail.com
*/
#include "GAMESystem.h"

int main(){

	GAMESystem *game = GAMESystem::getInstance();
	game->Game_Loop();
	
	return 0;
}