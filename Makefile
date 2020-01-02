#------------------------------
#
#  Balaram Behera
#  bbehera@ucsc.edu
#  CSE 101 - PA5
#  12/6/2019
#
#  File: Makefile
#
#-------------------------------


#------------------------------------------------------------------------------
#  make                     makes GraphSort
#  make clean               removes binaries
#  make memcheck           	tests GraphSort for memory leaks
#------------------------------------------------------------------------------


BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

GraphSort : GraphSort.o $(BASE_OBJECTS)
	$(LINK) GraphSort GraphSort.o $(BASE_OBJECTS)

GraphSort.o : GraphSort.c $(HEADERS)
	$(COMPILE) GraphSort.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) GraphSort GraphSort.o $(BASE_OBJECTS)

memcheck : GraphSort
	$(MEMCHECK) ./GraphSort
