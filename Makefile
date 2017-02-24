# CS109 quarter project
# simple makefile for testing

SOURCES		= Utility.cpp KnowledgeBase.cpp RuleBase.cpp SRI.cpp main.cpp
HEADERS		= Utility.hpp KnowledgeBase.hpp RuleBase.hpp SRI.hpp
EXEBIN		= sri
FLAGS		= -std=gnu++11
WARNING_FLAGS	= -std=gnu++11 -Wall

all : $(EXEBIN)

$(EXEBIN) : $(HEADERS) $(SOURCES)
	g++ $(FLAGS) -o $(EXEBIN) $(SOURCES)

clean :
	rm -f $(EXEBIN)

check :
	valgrind --leak-check=full $(EXEBIN)
