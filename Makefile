all: hw7Client hw7Server
hw7Client: main.cpp Knight.o Rabbit.o
	g++ -lpthread -std=c++14 -o hw7Client main.cpp Knight.o Rabbit.o
hw7Server: Server.cpp Log.o
	g++ -lpthread -std=c++14 -o hw7Server Server.cpp Log.o
Rabbit.o: Rabbit.cpp Rabbit.h
	g++ -std=c++14 -c Rabbit.cpp -o Rabbit.o
Knight.o: Knight.cpp Knight.h
	g++ -std=c++14 -c Knight.cpp -o Knight.o
Log.o: Log.cpp Log.h
	g++ -std=c++14 -c Log.cpp -o Log.o
clean:
	rm *.o
	rm hw7Client
	rm hw7Server