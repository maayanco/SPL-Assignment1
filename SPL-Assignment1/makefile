CC = g++
CFLAGS  = -g -Wall 
BOOST = -I/usr/local/boost/1.57.0/include/boost
#All Targets
all: cyber

#Tool invocations
#Executable "Address" depends on the files cyberdns
cyber: bin/cyberdns.o bin/cyberpc.o bin/cyberworm.o bin/cyberexpert.o bin/run.o 
	@echo 'Building target: cyber'
	@echo 'Invoking: c++ Linker'
	$(CC) -o bin/cyber bin/cyberdns.o bin/cyberpc.o bin/cyberworm.o bin/cyberexpert.o bin/run.o -L/usr/lib
	@echo 'Finished building target: cyber'
	

bin/cyberdns.o: src/cyberdns.cpp 
	$(CC) $(CFLAGS) -c -Linclude -o bin/cyberdns.o src/cyberdns.cpp
	
bin/cyberpc.o: src/cyberpc.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/cyberpc.o src/cyberpc.cpp

bin/cyberworm.o: src/cyberworm.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/cyberworm.o src/cyberworm.cpp

bin/cyberexpert.o: src/cyberexpert.cpp
	$(CC) $(CFLAGS) -c -Linclude -o bin/cyberexpert.o src/cyberexpert.cpp

bin/run.o: src/run.cpp
	$(CC) $(CFLAGS) -c -Linclude $(BOOST) -o bin/run.o src/run.cpp
#clean the build directory
clean:
	rm -f bin/*

