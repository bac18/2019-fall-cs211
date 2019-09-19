#define PDC_DLL_BUILD 1
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include "curses.h"
#include "panel.h"
using namespace std;

void show_page(WINDOW* win, vector<vector<vector<int>>> pages_vect, int page_number);

int main(int argc, char ** argv)
{
	WINDOW* main_win = nullptr;

	main_win = initscr();				// initializes the screen, sets up memory
	start_color();
	noecho();
	keypad(main_win, TRUE);

	WINDOW* main_window = newwin(LINES - 3, COLS, 3, 0);
	keypad(main_window, TRUE);
	wborder(main_window, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, 
		ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	refresh();
	wrefresh(main_window);

	WINDOW* options_bar_wind = newwin(3, COLS, 0, 0);
	keypad(options_bar_wind, TRUE);
	wborder(options_bar_wind, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
		ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	refresh();
	wrefresh(options_bar_wind);

	int opt_height = 1;
	int opt_width = 10;
	for (int i = 0; i < 21; i++)
		mvvline(opt_height, opt_width * i, '|', 1);

	const int num_of_options = 5;
	string menu_options[num_of_options] = { "File", "Edit", "View", "Format", "Help" };

	for (int i = 0; i < num_of_options; i++)
	{
		init_pair(2, COLOR_BLACK, COLOR_WHITE);
		attron(COLOR_PAIR(2));
		mvprintw(1, (opt_width * i) + (opt_width / 3), menu_options[i].c_str());
		attroff(COLOR_PAIR(2));
		refresh();
	}

	vector<vector<vector<int>>> pages;

	int cursor_x = 1;
	int cursor_y = 4;
	move(cursor_y, cursor_x);
	refresh();
	pages.push_back({});

	while (true)
	{
		int c = getch();

		if (c == KEY_RIGHT)
		{
			if (cursor_x < COLS - 2)
				move(cursor_y, ++cursor_x);
		}
		else if (c == KEY_LEFT)
		{
			if (cursor_x > 1)
				move(cursor_y, --cursor_x);
		}
		else if (c == KEY_DOWN)
		{
			if (cursor_y < LINES - 1)
				move(++cursor_y, cursor_x);
		}
		else if (c == KEY_UP)
		{
			if (cursor_y > 4)
				move(--cursor_y, cursor_x);
		}
		else if (c == ALT_0)
		{
			pages.push_back({});	// create new page of 45 lines
			mvwprintw(main_window, 30, 12, "%d", pages.size());
		}
		else if (c == ALT_1)
		{
			// go to next page
		}
		else if (c == KEY_DC)
		{
			if (cursor_x > 1)
			{
				move(cursor_y, --cursor_x);
				delch();
				move(cursor_y, COLS - 2);
				delch();
				mvaddch(cursor_y, COLS - 1, '|');                // reprint border wall after deleting
				move(cursor_y, cursor_x);
			}
			else if (cursor_x == 1)
			{
				move(--cursor_y, COLS);
			}

		}
		else
		{
			vector<int> here;

			int c = getch();

			here.push_back(c);

			for (int i = 0; i < here.size(); i++)
			{
				mvwprintw(main_window, 1, 1, "%d", c);
			}

			/*if (cursor_x < COLS - 2)
			{
				addch(c);
				move(cursor_y, ++cursor_x);
			}
			else
			{
				cursor_x = 0;
				move(++cursor_y, cursor_x);
				addch(c);
			}*/
		}
		// show_vectors() function

		wrefresh(main_window);
		refresh();
	}

	getch();
	endwin();
	return 0;
}



void show_page(WINDOW* win, vector<vector<vector<int>>> pages_vect, int page_number)
{
	for (int i = 0; i < 45; i++)
	{
		mvwprintw(win, 0, 0, "%d", pages_vect[page_number][i]);
	}
}