#include "../includes/box.h"
//holds up to 12 donuts (no more)
Box::Box() {
}

Box::~Box() {
}
//clear it out
void Box::clear() {
	donuts.clear();
}
//how many in the box

int Box::size() {
	return donuts.size();
}
//returns true if there is space in box and donut was added
//otherwise false (cant fit more than DOZEN)
bool Box::addDonut(DONUT &adonut) {
	if (donuts.size() == DOZEN)
		return false;

	donuts.push_back(adonut);
	return true;
}
