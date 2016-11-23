#include <Character.h>
using namespace std;

class Potion;

class Drow final: public Character {
private:
	// overrides the normal apply potion
	// to amplify effects by 50%
	virtual void applyPotion(Potion potion);

public:
	// uses template method pattern
	// to set stats of all different races
	virtual void setStats() = 0;

};
