all: programa

programa: main.o PatientArray.o
	g++ main.o PatientArray.o -o programa

main.o: main.cpp PatientArray.h
	g++ -c main.cpp -o main.o

PatientArray.o: PatientArray.cpp PatientArray.h
	g++ -c PatientArray.cpp -o PatientArray.o

clean:
	rm -f *.o programa