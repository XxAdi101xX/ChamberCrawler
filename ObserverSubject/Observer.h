#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Subject;

class Observer {
public:
	virtual void notify(Subject &whoNotified) = 0;
	virtual ~Observer();
};

#endif
