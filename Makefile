main: main.cpp Commands.h
	g++ main.cpp -o ping -fopenmp
	./ping list.txt 5
