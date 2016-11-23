#include <Character.h>


class Shade final: public Character {
public:
	virtual void setStats() override; // sets stats for a Shade

	// returns score, with 50% more due to
	// racial trait
	virtual int getScore() const override;

};


