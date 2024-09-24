output: main.o complex.o
	g++ main.o complex.o -o as1

main.o: main.cpp
	g++ -c main.cpp

complex.o: complex.cpp complex.h
	g++ -c complex.cpp

clean:
	rm *.o as1