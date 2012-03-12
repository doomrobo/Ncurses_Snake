#include "Food.h"
#include <ncurses.h>

Food::Food(int color_pair): colors(color_pair) {}

void Food::setLocation(coordinates loc) {
	location = loc;
}

void Food::draw() {
	attron(COLOR_PAIR(colors));
	mvaddch(location.second, location.first, '#');
	attroff(COLOR_PAIR(colors));
}
