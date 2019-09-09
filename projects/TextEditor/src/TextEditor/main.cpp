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


	mvhline(0, 0, '-', COLS);
	mvhline(2, 0, '-', COLS);
	int opt_width = 7;
	for (int i = 0; i < 21; i++)
	{
		mvvline(1, opt_width * i, '|', 1);
	}

	string menu_options[3] = { "File", "Edit", "View" };
	for (int i = 0; i < 3; i++)
	{
		mvprintw(1, (opt_width * i) + 2, menu_options[i].c_str());
	}

	int cursor_x = 0;
	int cursor_y = 3;
	move(cursor_y, cursor_x);

	refresh();
	
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
			{
				addch(c);
				move(cursor_y, ++cursor_x);
			}
			else
			{
				cursor_x = 0;
				move(++cursor_y, cursor_x);
				addch(c);
			}
		}
	}








	getch();
	endwin();
	return 0;
}
