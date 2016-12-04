CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = cc3k
OBJECTS = Main/Main.o Main/MainHelpers.o Cell/Cell.o Character/Character.o\
 		  Character/Dragon.o Character/Drow.o Character/Dwarf.o\
		  Character/Elf.o Character/Goblin.o Character/Halfling.o\
		  Character/Human.o Character/Merchant.o Character/Orc.o\
		  Character/Shade.o Character/Troll.o Character/Vampire.o\
		  Items/GoldPile.o Items/Item.o Items/Potion.o Generator/Generator.o\
		  Messaging/Messaging.o ObserverSubject/Observer.o ObserverSubject/Subject.o\
		  TextDisplay/TextDisplay.o Floor/Floor.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
