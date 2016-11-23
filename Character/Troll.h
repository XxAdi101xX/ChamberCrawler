#include <Character.h>
using namespace std;


class Character: public Subject {
public:
	// override adds 5 health at turn end
	virtual void endTurnRoutine() override;
	
	virtual void setStats() override; // sets Troll stats

};
