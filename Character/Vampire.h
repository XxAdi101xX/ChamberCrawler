#include <Character.h>
using namespace std;


class Vampire final: public Character {
private:
	// override adds health after attack
	virtual void postAttackRoutine(Character defender) override;

public:	
	virtual void setStats() override; // sets Vampire stats

};


