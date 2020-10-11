all: main.o calculator.o
	g++ -o main main.o calculator.o
calculator.o: calculator.cpp
	g++ -c calculator.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o main
