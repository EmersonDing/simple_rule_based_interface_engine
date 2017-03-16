# Group Number 9

CC     = g++
CFLAGS = -g -Wall -O0 -std=c++11 -D_SVID_SOURCE -pthread

all: server client

server: main.o TCPServerSocket.o sri.o knowledge.o rulebase.o TCPSocket.o
	${CC} -o server ${CFLAGS} main.o TCPServerSocket.o TCPSocket.o sri.o knowledge.o rulebase.o

client: main2.o TCPSocket.o sri.o 
	${CC} —o client  ${CFLAGS} main2.o TCPSocket.o sri.o

main.o:	main.cpp sri.hpp knowledge.hpp rulebase.hpp TCPServerSocket.h TCPSocket.h  
	${CC} -c ${CFLAGS} main.cpp

main2.o: main2.cpp sri.hpp knowledge.hpp rulebase.hpp TCPSocket.h
	${CC} -c ${CFLAGS} main.cpp

sri.o:	sri.cpp sri.hpp knowledge.hpp rulebase.hpp InputParser.hpp
	${CC} -c ${CFLAGS} sri.cpp

knowledge.o:	knowledge.cpp knowledge.hpp
	${CC} -c ${CFLAGS} knowledge.cpp

rulebase.o:	rulebase.cpp rulebase.hpp
	${CC} -c ${CFLAGS} rulebase.cpp

InputParser.o:	InputParser.cpp InputParser.hpp
	${CC} -c ${CFLAGS} InputParser.cpp

TCPServerSocket.o: TCPServerSocket.cpp TCPServerSocket.h TCPSocket.h
	${CC} -c ${CFLAGS} TCPServerSocket.cpp

TCPSocket.o: TCPSocket.cpp TCPSocket.h
	${CC} -c ${CFLAGS} TCPSocket.cpp
	

