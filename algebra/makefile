
all: main clean

main: metodo_de_gauss.o main.o 
	g++ -o main metodo_de_gauss.o main.o

metodo_de_gauss.o: metodo_de_gauss.cpp metodo_de_gauss.h
	g++ -c -o metodo_de_gauss.o metodo_de_gauss.cpp

main.o: main.cpp metodo_de_gauss.h
	g++ -c -o main.o main.cpp

clean:
	rm *.o