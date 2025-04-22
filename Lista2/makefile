all: programa

programa: main.o WaitingQueue.o
	g++ main.o WaitingQueue.o -o programa

main.o: main.cpp WaitingQueue.h
	g++ -c main.cpp -o main.o

WaitingQueue.o: WaitingQueue.cpp WaitingQueue.h
	g++ -c WaitingQueue.cpp -o WaitingQueue.o

clean:
	rm -f *.o programa