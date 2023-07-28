CC=g++
ST=--std=c++11
LOP=-o

MAIN=*
TAG=SyntheticGraphGenerator

all: clean code1

code1 :
	$(CC) $(ST) $(LOP) $(TAG) $(MAIN).cpp

clean :
	rm -f $(TAG)