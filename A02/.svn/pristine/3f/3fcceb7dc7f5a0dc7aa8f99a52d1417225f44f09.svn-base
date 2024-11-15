EIGEN_INC := $(shell pkg-config eigen3 --cflags)
ROOT_INC := -I$(shell root-config --cflags)
ROOT_LIBS := $(shell root-config --libs)
SRC := $(wildcard src/*.cpp)
CFLAGS := -std=c++17 -Wall

%.exe: main/%.cpp
	@echo "compiling $< --> $@"
	g++ -g $(CFLAGS) $< -o $@ -I src $(SRC) $(EIGEN_INC) $(ROOT_INC) $(ROOT_LIBS)

dump:
	@echo $(EIGEN_INC)
	@echo $(ROOT_INC)
	@echo $(ROOT_LIBS)
	@echo $(SRC)
