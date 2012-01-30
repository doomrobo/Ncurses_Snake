#ifndef SNAKE_H
#define SNAKE_H

#include <utility>
#include <vector>
#include <ncurses.h>

using namespace std;

typedef pair<unsigned int, unsigned int> coordinates;

class Snake {
private:
	void coordUp(coordinates&);
	void coordDown(coordinates&);
	void coordLeft(coordinates&);
	void coordRight(coordinates&);

	void fillBody(size_t len);

    int segChar;
	char *headChar;
     
    char headUp;
    char headDown;
    char headLeft;
    char headRight;

	coordinates head;
	vector<coordinates> segments;

	unsigned toGrow;
	int color;
	char direction;
	WINDOW *window;

	void (Snake::*segmentOp)(coordinates&);

public:
	Snake(int color_pair, coordinates startPos, size_t startLength, 
          char startDirection, WINDOW* win = stdscr);
	void advance();
	void turn(char);
	void grow(size_t);
	void draw();
	coordinates getHead();
};

#endif /*SNAKE_H*/
