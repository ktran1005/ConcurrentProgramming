# STD=--std=c++17 -pthread
# GCC=g++
# OBJ=obj
# BIN=bin

# obj/boat.o: src/boat.h src/boat.cpp
# 	[ -d $(OBJ) ] || mkdir -p $(OBJ)
# 	${GCC} ${STD} -c -o obj/boat.o src/boat.cpp

# obj/person.o: src/person.h src/person.cpp
# 	[ -d $(OBJ) ] || mkdir -p $(OBJ)
# 	${GCC} ${STD} -c -o obj/person.o src/person.cpp

	
# bin/main: obj/person.o obj/boat.o src/main.cpp
# 	[ -d $(BIN) ] || mkdir -p $(BIN)
# 	${GCC} ${STD} -o bin/main obj/person.o obj/boat.o src/main.cpp


# run: bin/main
# 	./bin/main
# clean:
# 	rm -f obj/*.o
# 	rm -f bin/main
# 	rm -r -f bin
# 	rm -r -f obj

STD=--std=c++17 -pthread
GCC=g++
OBJ=obj
BIN=bin

all: obj/boat.o obj/person.o

obj/boat.o: src/boat.h src/boat.cpp
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o obj/boat.o src/boat.cpp
obj/person.o: src/person.h src/person.cpp
	
	${GCC} ${STD} -c -o obj/person.o src/person.cpp
bin/main: obj/boat.o obj/person.o src/main.cpp
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${GCC} ${STD} -o bin/main obj/boat.o obj/person.o src/main.cpp
run: bin/main
	./bin/main
clean:
	rm -f obj/*.o
	rm -f bin/main
	rm -r -f bin
	rm -r -f obj