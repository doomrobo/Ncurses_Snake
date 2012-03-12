#include <ncurses.h>
#include <iostream>
#include <locale.h>
#include <ctime>
#include <cstdlib>

#include "snake.h"
#include "Food.h"

int main() {
	initscr();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    curs_set(0);

	srand(time(NULL));
    
	int snake_color = 1;
	int food_color = 2;
    assume_default_colors(COLOR_RED, COLOR_BLACK);
	start_color();
	init_pair(food_color, COLOR_YELLOW, COLOR_BLACK);
    init_pair(snake_color, COLOR_RED, COLOR_BLACK);

	int y, x;
	getmaxyx(stdscr, y, x);

	Food food(food_color);
	coordinates foodLocation = make_pair(20, 10);
	food.setLocation(foodLocation);
    
	Snake snake(snake_color, coordinates(10,10), 5, 'r');
	snake.draw();
	refresh();
	coordinates headPos = snake.getHead();
	vector<coordinates> segments;

	bool self_collision = false;

	while (1) {

		usleep(100000);

		int ch = getch();
		switch(ch) {
			//case KEY_UP:
			case 'k':
				snake.turn('u');
				break;
			//case KEY_DOWN:
			case 'j':
				snake.turn('d');
				break;
			//case KEY_LEFT:
			case 'h':
				snake.turn('l');
				break;
			//case KEY_RIGHT:
			case 'l':
				snake.turn('r');
				break;
			default:
				break;
        }

		snake.advance();
		headPos = snake.getHead();

		if (headPos == foodLocation) {
			snake.grow(1);
			foodLocation = make_pair(rand()%x, rand()%y);
			food.setLocation(foodLocation);
		}

		segments = snake.getSegments(); // Now check for self-collision
		for (vector<coordinates>::iterator it = segments.begin();
			 it != segments.end(); it++) {
			if (headPos == *it) {
				self_collision = true;
				break;
			}
		}
		if (self_collision == true)
			break;

		if (headPos.first >= x || headPos.first == -1
			|| headPos.second >= y || headPos.second == -1)
			break;

        clear();
		snake.draw();
		food.draw();
		refresh();
	}

	nodelay(stdscr, false);
	getch();

	endwin();
	return 0;
}
