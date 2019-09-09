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
	WINDOW* main_window = nullptr;

	main_window = initscr();				// initializes the screen, sets up memory
	start_color();
	noecho();
	keypad(main_window, TRUE);
	keypad(stdscr, TRUE);

	int opt_height = 1;
	int opt_width = 10;
	mvhline(0, 0, '-', COLS);
	mvhline(2, 0, '-', COLS);
	for (int i = 0; i < 21; i++)
		mvvline(opt_height, opt_width * i, '|', 1);

	const int num_of_options = 5;
	string menu_options[num_of_options] = { "File", "Edit", "View", "Format", "Help" };

	for (int i = 0; i < num_of_options; i++)
	{
		mvprintw(1, (opt_width * i) + (opt_width / 3), menu_options[i].c_str());
		refresh();
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
			if (cursor_y > 3)
				move(--cursor_y, cursor_x);
		}
		else if (c == KEY_BACKSPACE)
		{
			move(cursor_y, --cursor_x);
			addch('<');
			refresh();
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

		refresh();
		}
	}

	getch();
	endwin();
	return 0;
}
