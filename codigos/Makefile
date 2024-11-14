CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

all: costos main

costos: costos.cpp
	${CXX} ${CXXFLAGS} costos.cpp -o costos

main: main.cpp
	${CXX} ${CXXFLAGS} main.cpp -o main

run-costos: costos
	./costos

run-main: main
	./main

clean:
	rm -f costos main