#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

class CSnake:public CFramedWindow
{
private:
	vector<CPoint> segments;
	int level;
	bool pause=true;
	bool help=true;
	bool died=false;
	int dir = KEY_RIGHT;
	int speed=1;
public:
  CSnake(CRect r, char _c = ' ');
	void printHelp();
	void paint();
	bool handleEvent(int key);
	void printSnake();
	void gameReset();
	bool moveSnake();
};

#endif
