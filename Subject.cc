#include "Subject.h"

bool Subject::attach(Observer *o) {
	observers.emplace_back(o);
	return true;
}

void Subject::detach(Observer *o) {
	observers.erase(o);
}

void Subject::notifyObservers() {
	for (auto &ob: observers) {
		ob->notify();
	}
}

Subject::~Subject() {}
