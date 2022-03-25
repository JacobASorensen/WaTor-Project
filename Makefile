.PHONY: all clean

CXXFLAGS =  -g -O3 -Wpedantic -Wall -Wextra -Wmisleading-indentation -Wunused -Wuninitialized -Wshadow -Wconversion -std=c++17
# -Werror
OBJS = JS_WaTor

all: ${OBJS}

JS_WaTor: WorldT.o Entities.o GodT.o Display.o
WorldT.o: WorldT.h
Entities.o: Entities.h WorldT.h
GodT.o: GodT.h WorldT.h Entities.h
Display.o: Display.h WorldT.h Entities.h GodT.h

clean:
	rm -f ${OBJS} *.o 

clear:
	make clean
	clear
	clear
	make
