output : main.o sin_lookup_table.o
		g++ main.o sin_lookup_table.o -o as4

main.o: main.cpp
		g++ -c main.cpp

sin_lookup_table.o : sin_lookup_table.h sin_lookup_table.cpp
					g++ -c sin_lookup_table.cpp

clean:
		rm *.o as4