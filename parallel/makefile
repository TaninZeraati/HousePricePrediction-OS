CC := g++ -std=c++11

all: HousePricePrediction.out

HousePricePrediction.out: main.o csv_handler.o classifier.o
		$(CC) -pthread main.o csv_handler.o classifier.o -o HousePricePrediction.out

main.o: main.cpp csv_handler.h classifier.h
		$(CC) -c main.cpp -o main.o

csv_handler.o: csv_handler.cpp csv_handler.h
		$(CC) -c csv_handler.cpp -o csv_handler.o

classifier.o: classifier.cpp classifier.h csv_handler.h
	$(CC) -c classifier.cpp -o classifier.o


.PHONY: clean
clean:
	rm -r *.o *.out