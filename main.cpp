#include <ncursesw/ncurses.h>
#include <iostream>
#include <locale.h>

#include "snake.h"

int main() {
	initscr();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    curs_set(0);
    
	int color = 1;
    assume_default_colors(COLOR_RED, COLOR_BLACK);
	start_color();
    init_pair(color, COLOR_RED, COLOR_BLACK);

	int y, x;
	getmaxyx(stdscr, y, x);
    
	Snake snake(color, coordinates(10,10), 5, 'r');
	snake.draw();
	refresh();
	coordinates pos = snake.getHead();
	while (1) {

		usleep(100000);

		int ch = getch();
		std::cerr << ch << endl;
		switch(ch) {
			case KEY_UP:
				snake.turn('u');
				break;
			case KEY_DOWN:
				snake.turn('d');
				break;
			case KEY_LEFT:
				snake.turn('l');
				break;
			case KEY_RIGHT:
				snake.turn('r');
				break;
			default:
				break;
        }


		snake.advance();
		pos = snake.getHead();

		if (pos.first >= x || pos.first == -1
			|| pos.second >= y || pos.second == -1)
			break;

        clear();
		snake.draw();
		refresh();
	}

    nodelay(stdscr, false);
	getch();

	endwin();
	return 0;
}
