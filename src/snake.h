#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"

class CSnake:public CFramedWindow
{
private:
	vector<CPoint> segments;
	
public:
  CSnake(CRect r, char _c = ' ');
	void printHelp();
	void paint();
	bool handleEvent(int key);
};

#endif
