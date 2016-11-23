#include <Character.h>
using namespace std;


class Goblin final;: public Character {
private:
	// overrides to add 5 gold if target is killed
	virtual void postAttackRoutine(Character defender) override;

public:
	virtual void setStats() override; // sets Goblin stats

};
