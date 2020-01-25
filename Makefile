# example4/Makefile
CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror=vla -MMD -g
OBJECTS=main.o block.o board.o divider.o iBlock.o jBlock.o lBlock.o level.o levelFour.o levelOne.o levelThree.o levelTwo.o levelZero.o oBlock.o observer.o sBlock.o subject.o tBlock.o textDisplay.o zBlock.o hint.o graphicalDisplay.o window.o 
DEPENDS=${OBJECTS:.o=.d}
EXEC=quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean
