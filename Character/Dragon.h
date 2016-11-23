#include <Character.h>
using namespace std;


class Dragon final: public Character {
private:
	GoldPile& dragonHoard;
public:
	// overrides to unbind the dragon hoard
        virtual void deathRoutine(Character killer) override;

	// checks whether or not to turn hostile
	virtual void endTurnRoutine() override;
	virtual void setStats() override; // set Dragon stats

};


