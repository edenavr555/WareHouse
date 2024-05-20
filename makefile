
all: clean compile link

link:
	g++ -o bin/warehouse bin/parser.o bin/Customer.o bin/Volunteer.o bin/WareHouse.o bin/main.o bin/Action.o bin/Order.o

compile:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o  bin/parser.o src/parser.cpp 
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Volunteer.o src/Volunteer.cpp 
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Customer.o src/Customer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/WareHouse.o src/WareHouse.cpp 
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/main.o src/main.cpp 
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Action.o src/Action.cpp 
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Order.o src/Order.cpp 

clean:
	rm -f bin/*.o

