#define PDC_DLL_BUILD 1
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include "curses.h"
#include "panel.h"
using namespace std;

void show_page(WINDOW* win, vector<vector<vector<int>>> pages_vect, int page_number);

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		string user_file_name;
		getline(cin, user_file_name);

		ifstream infile;
		infile.open(user_file_name);

		if (!infile)
		{
			cout << "Error" << endl;
			exit(1);
		}

		string line;
		while (infile >> line)
		{
			cout << line << endl;
		}

		infile.close();
	}


	WINDOW* main_win = nullptr;
	main_win = initscr();				// initializes the screen, sets up memory
	start_color();
	noecho();
	keypad(main_win, TRUE);

	WINDOW* main_window = newwin(LINES - 3, COLS, 3, 0);
	keypad(main_window, TRUE);
	wborder(main_window, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,			// sets up the main interactive window
		ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	refresh();
	wrefresh(main_window);													

	WINDOW* options_bar_wind = newwin(3, COLS, 0, 0);
	keypad(options_bar_wind, TRUE);
	wborder(options_bar_wind, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,		// sets up the top-of-window options bar
		ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	refresh();
	wrefresh(options_bar_wind);

	int opt_bar_wind_height = 1;
	int opt_bar_wind_width = 10;
	for (int i = 0; i < 21; i++)
		mvvline(opt_bar_wind_height, opt_bar_wind_width * i, '|', 1);

	const int num_of_options = 5;
	string menu_options[num_of_options] = { "File", "Edit", "View", "Format", "Help" };

	for (int i = 0; i < num_of_options; i++)
	{
		init_pair(2, COLOR_BLACK, COLOR_WHITE);
		attron(COLOR_PAIR(2));
		mvprintw(1, (opt_bar_wind_width * i) + (opt_bar_wind_width / 3), menu_options[i].c_str());	// prints menu_options 
		attroff(COLOR_PAIR(2));																		// onto options bar
		refresh();
	}

	vector<vector<char>> page;

	int cursor_x = 1;
	int cursor_y = 1;
	wmove(main_window, cursor_y, cursor_x);
	wrefresh(main_window);
	//page.push_back({});

	bool stillRunning = true;
	while (stillRunning)
	{
		int c = wgetch(main_window);

		if (c == '0')
			stillRunning = false;
		else if (c == KEY_RIGHT)
		{
			if (cursor_x < COLS - 2)				// if cursor isn't at the right most column, move cursor one to the right 
				wmove(main_window, cursor_y, ++cursor_x);
		}
		else if (c == KEY_LEFT)
		{
			if (cursor_x > 1)
				wmove(main_window, cursor_y, --cursor_x);			// if cursor isn't at the left most column, move cursor one to the left
		}
		else if (c == KEY_DOWN)
		{
			if (cursor_y < LINES - 5)
				wmove(main_window, ++cursor_y, cursor_x);			// if cursor isn't at the bottom most row, move cursor down one
		}
		else if (c == KEY_UP)
		{
			if (cursor_y > 1)  
				wmove(main_window, --cursor_y, cursor_x);			// if cursor isn't at the top most row, move cursor up one
		}
		else if (c == ALT_0)
		{
			page.push_back({});	// create new page of 45 lines
			mvwprintw(main_window, 30, 12, "%d", page.size());
		}
		else if (c == ALT_1)
		{
			// go to next page
		}
		else if (c == KEY_DC)
		{
			if (cursor_x > 1)
			{
				wmove(main_window, cursor_y, --cursor_x);
				wdelch(main_window);
				wmove(main_window, cursor_y, COLS - 2);
				wdelch(main_window);
				mvwaddch(main_window, cursor_y, COLS - 1, '|');                // reprint border wall after deleting
				wmove(main_window, cursor_y, cursor_x);
			}
			/*else if (cursor_x == 1)
			{
				wmove(main_window, --cursor_y, COLS);
				wrefresh(main_window);
			}*/

		}
		else
		{
			/*vector<char> here;

			char c = getch();
			here.push_back(c);

			for (int i = 0; i < here.size(); i++)
			{
				wprintw(main_window, "%c", here[i]);
				wrefresh(main_window);
				refresh();
			}*/

			if (cursor_x < COLS - 2)
			{
				waddch(main_window, c);
				wmove(main_window, cursor_y, ++cursor_x);
			}
			else
			{
				cursor_x = 0;
				wmove(main_window, ++cursor_y, cursor_x);
				waddch(main_window, c);
			}
		}
		// show_vectors() function

		wrefresh(main_window);
		refresh();
	}

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