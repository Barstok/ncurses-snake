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
        printl("Also, dont die.");
        gotoyx(y + 7, x + 2);
        printl("press 'p' or 'r' to play or 'h' for help");
}

void CSnake::paint(){
	CFramedWindow::paint();
	printHelp();
}

bool handleEvent(int key){
	
}
