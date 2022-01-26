#include "snake.h"

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
	srand(time(NULL));
	gameReset();
	generateFood();
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
		gotoyx(geom.topleft.y-2,geom.topleft.x);
		printl("| HIGHSCORE: %d |",highscore);
		gotoyx(geom.topleft.y-1,geom.topleft.x);
		printl("| LEVEL: %d |",level);
		if(pause&&help) printHelp();
		if(!pause){
			printFood();
			printSnake();
		}
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

void CSnake::gameReset(){
	segments.clear();
	level=1;
	int headPosX = rand() % (geom.size.x - 5) + 1;
    int headPosY = rand() % (geom.size.y - 3) + 1;
    segments.push_back(CPoint(headPosX, headPosY));
    segments.push_back(CPoint(headPosX - 1, headPosY));
    segments.push_back(CPoint(headPosX - 2, headPosY));
}

void CSnake::generateFood(){
	while(1){
		food.x=(rand() % (geom.size.x - 2)) + 1;
		food.y=(rand() % (geom.size.y - 2)) + 1;
		for (unsigned long i = segments.size()-1; i > 0; i--) {
            if(food.y!=segments[i].y||food.x!=segments[i].x) return;
        }
	}
}

int CSnake::collisionCheck(){
	for (unsigned long i = segments.size()-1; i > 0; i--) {
            if(segments[0].y==segments[i].y&&segments[0].x==segments[i].x) return 1;
        }
     if(segments[0].y==food.y&&segments[0].x==food.x) return 2;
     
     return 0;
}

bool CSnake::moveSnake() {
        if (pause) {
            return true;
        }
        int check = collisionCheck();
        if(check==1){
			died=!died;
			if(level>highscore) highscore=level;
			return false;
		}
        if(check==2){
			generateFood();
			level++;
			CPoint tail = segments[segments.size()-1];
			segments.push_back(tail);
		}
		for (unsigned long i = segments.size() - 1; i > 0; i--) {
				segments[i] = segments[i - 1];
		}
        if (dir == KEY_DOWN) {
            segments[0] += CPoint(0, 1);
        } else if (dir == KEY_UP) {
            segments[0] += CPoint(0, -1);
        } else if (dir == KEY_RIGHT) {
            segments[0] += CPoint(1, 0);
        } else if (dir == KEY_LEFT) {
            segments[0] += CPoint(-1, 0);
        }
        if (segments[0].x == 0) {
            segments[0].x = geom.size.x - 2;
        }
        if (segments[0].x == geom.size.x - 1) {
            segments[0].x = 1;
        }
        if (segments[0].y == 0) {
            segments[0].y = geom.size.y - 2;
        }
        if (segments[0].y == geom.size.y - 1) {
            segments[0].y = 1;
        }
        return true;
}

void CSnake::printFood(){
	gotoyx(food.y + geom.topleft.y, food.x + geom.topleft.x);
	printc('0');
}

void CSnake::printSnake(){
	moveSnake();
	gotoyx(segments[0].y + geom.topleft.y, segments[0].x + geom.topleft.x);
        printc('*');
	for (unsigned i = 1; i < segments.size(); i++) {
            gotoyx(segments[i].y + geom.topleft.y, segments[i].x + geom.topleft.x);
            printc('+');
        }
}

bool CSnake::handleEvent(int key){
	if(key==ERR){
		if(level>20) return true;
		speed+=level;
		if(speed>=20){
			speed=0;
			return true;
		}
		return false;
	}
	if(!died&&tolower(key)=='r'){
		if(pause) pause=false;
		gameReset();
		return true;
	}
	if(pause&&tolower(key)=='h'){
		help=!help;
		return true;
	}
	if(!died&&tolower(key)=='p'){
		pause=!pause;
		return true;
	}
	if(died&&tolower(key)=='r'){
		died=false;
		gameReset();
		return true;
	}
	if (!died && !pause && (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT)) {
            if ((key == KEY_UP && dir != KEY_DOWN) || (key == KEY_DOWN && dir != KEY_UP) ||
                (key == KEY_LEFT && dir != KEY_RIGHT) || (key == KEY_RIGHT && dir != KEY_LEFT)) {
                dir = key;
            }
            return true;
            }
	return CFramedWindow::handleEvent(key);
}
