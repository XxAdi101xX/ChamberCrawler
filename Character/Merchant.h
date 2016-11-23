#include <Character.h>


class Merchant final: public Character {
public:
	// overrides to drop merchant goldpile upon death
        virtual void deathRoutine(Character& killer) override;
	virtual void setStats() override; // sets Merchant stats

};


