CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

all: randomcostos main

costos: costos.cpp
	${CXX} ${CXXFLAGS} costos.cpp -o costos

randomcostos: random-costos.cpp
	${CXX} ${CXXFLAGS} random-costos.cpp -o randomcostos

main: main.cpp
	${CXX} ${CXXFLAGS} main.cpp -o main

run-costos: costos
	./costos

run-random: randomcostos
	./randomcostos

run-main: main
	./main

python:
	python graficos.py

clean:
	rm -f costos main randomcostos
