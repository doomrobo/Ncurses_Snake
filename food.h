#ifndef FOOD_H
#define FOOD_H

#include <utility>

typedef std::pair<unsigned int, unsigned int> coordinates;

class Food {
private:
	coordinates location;
	int colors;

public:
	Food(int color_pair);
	void setLocation(coordinates loc);
	void draw();
};

#endif /* FOOD_H */
