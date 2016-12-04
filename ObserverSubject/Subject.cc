#include "Subject.h"
#include <algorithm>
#include <iostream>

bool Subject::attach(std::shared_ptr<Observer> o) {
	observers.emplace_back(o);
	return true;
}

void Subject::detach(std::shared_ptr<Observer> o) {
	observers.erase(std::find(observers.begin(), observers.end(), o));
}

void Subject::notifyObservers() {
	for (auto &ob: observers) {
		std::cout << "Notifying" << std::endl;
		ob->notify(*this);
		std::cout << "end Notify" << std::endl;
	}
}

Subject::~Subject() {}
