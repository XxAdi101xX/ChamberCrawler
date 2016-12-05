#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include "Observer.h"
#include "../Info/Info.h"
#include <vector>
#include <memory>

class Subject {
	std::vector<Observer*> observers;
public:
	bool attach(Observer*);
	void detach(Observer*);
	virtual Info getInfo() const = 0;
	void notifyObservers();
	virtual ~Subject() = 0;
};

#endif
