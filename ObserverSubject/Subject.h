#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include "Observer.h"
#include <vector>

class Subject {
	std::vector<Observer *> observers;
public:
	bool attach(Observer *o);
	void detach(Observer *o);
	void notifyObservers();
	virtual ~Subject() = 0;
}

#endif
