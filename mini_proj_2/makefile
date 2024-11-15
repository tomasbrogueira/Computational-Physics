CC = g++
CFLAGS = -std=c++17 

ROOT_INC = `root-config --cflags`
ROOT_LIBS = `root-config --libs`
INC = lightmap.cpp


run:
	$(CC) main.cpp $(INC) $(CFLAGS) $(ROOT_INC) $(ROOT_LIBS) -o run main.cpp