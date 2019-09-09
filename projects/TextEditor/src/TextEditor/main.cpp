#define PDC_DLL_BUILD 1
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include "curses.h"
#include "panel.h"

using namespace std;

int main(int argc, char ** argv)
{
	initscr();				// initializes the screen, sets up memory
	noecho();
	keypad(stdscr, TRUE);

	int cursor_x = 0;
	int cursor_y = 0;
	move(cursor_y, cursor_x);
	
	while (true)
	{
		int c = getch();

		if (c == KEY_RIGHT)
		{
			if (cursor_x < COLS - 1)
				move(cursor_y, ++cursor_x);
		}
		else if (c == KEY_LEFT)
		{
			if (cursor_x > 0)
				move(cursor_y, --cursor_x);
		}
		else if (c == KEY_DOWN)
		{
			if (cursor_y < LINES - 1)
				move(++cursor_y, cursor_x);
		}
		else if (c == KEY_UP)
		{
			if (cursor_y > 0)
				move(--cursor_y, cursor_x);
		}
		else
		{
			if (cursor_x < COLS - 1)
				move(cursor_y, ++cursor_x);
		}
	}








	getch();
	endwin();
	return 0;
}
