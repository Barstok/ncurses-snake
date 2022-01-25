#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"
#include <vector>

class CSnake:public CFramedWindow
{
private:
	vector<CPoint> segments;
	int level;
	bool pause=true;
	bool help=true;
	bool died=false;
	
public:
  CSnake(CRect r, char _c = ' ');
	void printHelp();
	void paint();
	bool handleEvent(int key);
	void printSnake();
};

#endif
