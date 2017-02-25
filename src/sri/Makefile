# Group Number 9

CC     = g++
CFLAGS = -g -Wall -O0 -std=c++11 -D_SVID_SOURCE

sri:	main.o sri.o knowledge.o rulebase.o InputParser.o
	${CC} -o sri ${CFLAGS} main.o sri.o knowledge.o rulebase.o InputParser.o

main.o:		main.cpp sri.hpp knowledge.hpp rulebase.hpp
	${CC} -c ${CFLAGS} main.cpp

sri.o:		sri.cpp sri.hpp knowledge.hpp rulebase.hpp InputParser.hpp
	${CC} -c ${CFLAGS} sri.cpp

knowledge.o:	knowledge.cpp knowledge.hpp
	${CC} -c ${CFLAGS} knowledge.cpp

rulebase.o:	rulebase.cpp rulebase.hpp
	${CC} -c ${CFLAGS} rulebase.cpp

InputParser.o:	InputParser.cpp InputParser.hpp
	${CC} -c ${CFLAGS} InputParser.cpp

