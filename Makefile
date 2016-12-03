CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = a4q3a
OBJECTS = Main/Main.o Generator/Generator.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
