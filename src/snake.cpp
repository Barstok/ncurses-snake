#include "snake.h"

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
}
void CSnake::printHelp(){
	int x = geom.topleft.x, y = geom.topleft.y;
	gotoyx(y + 2, x + 2);
        printl("Use arrows to move snake");
        gotoyx(y + 4, x + 2);
        printl("Eat as much food as you can.");
        gotoyx(y + 5, x + 2);
        printl("press 'p' or 'r' to play or 'h' for help");
}

void CSnake::paint(){
	CFramedWindow::paint();
	
	if(!died){
		gotoyx(geom.topleft.y-1,geom.topleft.x);
		printl("| LEVEL: %d |",level);
		if(pause&&help) printHelp();
		if(!pause) printSnake();
	}
	else{
		gotoyx((geom.topleft.y+geom.size.y)/2,geom.topleft.x+15);
		printl("GAME OVER");
		gotoyx((geom.topleft.y+geom.size.y)/2+1,geom.topleft.x+13);
		printl("Your score: %d",level);
		gotoyx((geom.topleft.y+geom.size.y)/2+2,geom.topleft.x+7);
		printl("Press r to restart the game");
	}
}

void CSnake::printSnake(){
	
}

bool CSnake::handleEvent(int key){
	if(pause&&tolower(key)=='h'){
		help=!help;
		return true;
	}
	return CFramedWindow::handleEvent(key);
}
