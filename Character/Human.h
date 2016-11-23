#include <Character.h>
using namespace std;


class Human final: public Character {
public:
	// overrides to drop two normal goldpile upon death
        virtual void deathRoutine(Character killer) override;

	virtual void setStats() override; // sets Human stats

};
