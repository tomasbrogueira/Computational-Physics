EIGEN_INC := $(shell pkg-config eigen3 --cflags)
ROOT_INC := -I$(shell root-config --cflags)
ROOT_LIBS := $(shell root-config --libs)

SRC := $(wildcard src/*.cpp)
HDR := $(wildcard src/*.h)
OBJ := $(patsubst src/%.cpp,bin/%.o,$(SRC))
VPATH := main:src


C_FLAGS := -std=c++17 -Wall 

main.exe: bin/main.o $(OBJ) 
	@echo "----------- linking $< --> $@"
	g++ $(C_FLAGS) $< $(OBJ) -o ./bin/$@  $(ROOT_LIBS)

bin/%.o: %.cpp $(HDR) 
	@echo -e "\n----------- compiling \e[32m$<\e[0m\t --> \e[36m$@\e[0m"
	g++ $(C_FLAGS) -c $< -o $@ -I src $(EIGEN_INC) $(ROOT_INC) 

%.exe: bin/%.o $(OBJ) 
	@echo "----------- linking $< --> $@"
	g++ $(C_FLAGS) $< $(OBJ) -o ./bin/$@  $(ROOT_LIBS) 

dump:
	@echo $(EIGEN_INC)
	@echo $(ROOT_INC)
	@echo $(ROOT_LIBS)
	@echo SRC: $(SRC)
	@echo HDR: $(HDR)
	@echo OBJ: $(OBJ)

clean:
	@rm -fv $(wildcard main/*~)
	@rm -fv $(wildcard src/*~)
	@rm -fv $(wildcard *~)
	@rm -fv $(wildcard bin/*.exe)
	@rm -fv $(wildcard bin/*.o)
