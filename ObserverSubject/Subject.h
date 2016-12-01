#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include "Observer.h"
#include <vector>
#include <memory>

class Subject {
	std::vector<std::shared_ptr<Observer>> observers;
public:
	bool attach(std::shared_ptr<Observer>);
	void detach(std::shared_ptr<Observer>);
	void notifyObservers();
	virtual ~Subject() = 0;
}

#endif
