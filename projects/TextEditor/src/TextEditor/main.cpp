#define PDC_DLL_BUILD 1
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include "curses.h"

using namespace std;

int main(int argc, char ** argv)
{
	initscr();				// initializes the screen, sets up memory
	noecho();
	keypad(stdscr, TRUE);

	int height = 30;
	int width = 120;
	int starty = 0;
	int startx = 0;

	WINDOW* win = newwin(height, width, starty, startx);
	refresh();
	box(win, 0, 0);
	wrefresh(win);

	int curs_x = 1;
	int curs_y = 1;
	move(curs_y, curs_x);
	refresh();

	while (true)
	{
		getch();
		curs_x++;
		move(curs_y, curs_x);
		refresh();
	}

	getch();

	endwin();
	return 0;
}
