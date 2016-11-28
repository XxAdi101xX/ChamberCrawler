#ifndef _ELF_H_
#define _ELF_H_

#include "Character.h"
class Generator;


class Elf final: public Character {
private:
	int extraAttacks; // how many more attacks elf can do

	// overrides postAttackRoutine to attack again if
        // it hasn't and the target is not a Drow
        virtual void postAttackRoutine(Character& defender, bool hit,
                Generator& rng) override;

public:
	Elf(int wallet); // ctor

};


#endif


