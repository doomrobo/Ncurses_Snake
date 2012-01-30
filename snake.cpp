#include <iostream>
#include <vector>
#include <cstdlib>

#include "snake.h"

// Remember that the origin is the top left! //

inline void Snake::coordUp(coordinates &c) {
	c.second--;
}
inline void Snake::coordDown(coordinates &c) {
	c.second++;
}
inline void Snake::coordLeft(coordinates &c) {
	c.first--;
}
inline void Snake::coordRight(coordinates &c) {
	c.first++;
}

void Snake::fillBody(size_t len) {
	coordinates current = head;
	
	for (int i = 0; i < len-1; i++) {
		(this->*segmentOp)(current);
		segments.push_back(current);
        //std::cerr << "now " << segments.size() << " in segments<>\n";
	}
}

Snake::Snake(int color_pair, coordinates startPos, size_t startLength, 
             char startDirection, WINDOW* win) {
/*

    //segChar = 0x2588; // █ - full block char
    segChar = 0x25A0; // ■ - square char
     
    headUp     = 0x25B2; // ▲ - up-pointing triangle
    headDown   = 0x25BC; // ▼ - down-pointing triangle
    headLeft   = 0x25C0; // ◀ - left-pointing triangle
    headRight  = 0x25B6; // ▶ - right-pointing triangle

*/
	segChar    = ' ' | A_REVERSE;
	headUp     = '^';
	headDown   = 'v';
	headLeft   = '<';
	headRight  = '>';

	toGrow = 0;             // Snake grows by one segment each advance() call
                            // for however many toGrow are left
	color = color_pair;
	head = startPos;
	direction = startDirection;
	window = win;
    
	// Make a function pointer so it doesn't have to check the direction each function call
	switch (direction) {		// Segments are pushed in the opposite direction
								// of the head
		case 'u':
			headChar = &headUp;
			segmentOp = &Snake::coordDown;
			fillBody(startLength);
			segmentOp = &Snake::coordUp;
			break;
		case 'd':
			headChar = &headDown;
			segmentOp = &Snake::coordUp;
			fillBody(startLength);
			segmentOp = &Snake::coordDown;
			break;
		case 'l':
			headChar = &headLeft;
			segmentOp = &Snake::coordRight;
			fillBody(startLength);
			segmentOp = &Snake::coordLeft;
			break;
		case 'r':
			headChar = &headRight;
			segmentOp = &Snake::coordLeft;
			fillBody(startLength);
			segmentOp = &Snake::coordRight;
			break;
		default:
			std::cerr << "Invalid Input!\n";
			exit(-1);
			break;
	}
}

void Snake::advance() {
	// Start advancing the segments at the end of the overlapping
	// segments to avoid redundancy
	for (int i = segments.size()-1-toGrow; i > 0; i--) {
		segments.at(i) = segments.at(i-1);
	}
	
	segments.at(0) = head;
	(this->*Snake::segmentOp)(head);
	
    if (toGrow > 0)
        toGrow--;   // Just grew by one
}

void Snake::turn(char dir) {
	switch(dir) {
		case 'u':
			if (direction != 'u' && direction != 'd') {
				headChar = &headUp;
				std::cerr << "Direction is up\n";
				segmentOp = &Snake::coordUp;
			}
			break;
		case 'd':
			if (direction != 'u' && direction != 'd') {
				std::cerr << "Down\n";
				headChar = &headDown;
				segmentOp = &Snake::coordDown;
			}
			break;
		case 'l':
			cerr << "Trying to move left\n";
			if (direction != 'l' && direction != 'r') {
				headChar = &headLeft;
				segmentOp = &Snake::coordLeft;
			}
			break;
		case 'r':
			if (direction != 'l' && direction != 'r') {
				headChar = &headRight;
				segmentOp = &Snake::coordRight;
			}
			break;
		default:
			return;
	}
	direction = dir;
}

/*
  length segments are pushed to segments vector with the same
  coordinates as the tail. This produces overlapping segments
  that are drawn out each advance() call.
*/

void Snake::grow(size_t length) {
	toGrow = length;
	for (int i = 0; i < length; i++) {
		segments.push_back(segments.at(segments.size()-1)); // Push back the tail over itself (overlap)
	}
}

void Snake::draw() {
	attron(COLOR_PAIR(color));

	mvwaddch(window, head.second, head.first, *headChar);
	for (int i = 0; i < segments.size()-toGrow; i++) {
		//std::cerr << "Printing (" << segments.at(i).second << "," << segments.at(i).first << ")\n" << std::flush;
		mvwaddch(window, segments.at(i).second, segments.at(i).first, segChar);
	}

	attroff(COLOR_PAIR(color));
}

coordinates Snake::getHead() {
	return head;
}
