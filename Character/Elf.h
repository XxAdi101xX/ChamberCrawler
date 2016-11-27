#ifndef _ELF_H_
#define _ELF_H_

#include "Character.h"
class Generator;


class Elf final: public Character {
private:
	bool attackedTwice;

public:
	Elf(int wallet); // ctor

	// overrides postAttackRoutine to attack again if
	// it hasn't and the target is not a Drow
	virtual void postAttackRoutine(Character* defender) override;

};


#endif


