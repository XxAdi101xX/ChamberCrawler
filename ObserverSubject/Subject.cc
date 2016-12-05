#include "Subject.h"
#include <algorithm>
#include <iostream>

bool Subject::attach(Observer* o) {
	observers.emplace_back(o);
	return true;
}

void Subject::detach(Observer* o) {
	observers.erase(std::find(observers.begin(), observers.end(), o));
}

void Subject::notifyObservers() {
	for (auto &ob: observers) {
		ob->notify(*this);
	}
}

Subject::~Subject() {}
