shra: main.o guest.o cleaner.o
	g++ main.o guest.o cleaner.o -o shra

main.o: main.cpp hotel.h
	g++ -std=c++14 -c main.cpp

guest.o: guest.cpp hotel.h
	g++ -std=c++14 -c guest.cpp

cleaner.o: cleaner.cpp hotel.h
	g++ -std=c++14 -c cleaner.cpp

clean:
	rm main.o cleaner.o guest.o shra