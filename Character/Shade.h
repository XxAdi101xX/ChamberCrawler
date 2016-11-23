#include <Character.h>
using namespace std;


class Shade final: public Character {
public:
	// mutators :
	
	virtual void setStats() override; // sets stats for a Shade

	// accessors:

	// returns score, with 50% more due to
	// racial trait
	virtual int getScore() const override;

};
