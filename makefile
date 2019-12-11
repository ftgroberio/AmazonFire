# This makefile was generated using a template provided from 
# Harlan James <waldroha@oregonstate.edu>
#
PROJ = SaveThePie
$(CXX) = g++
SRC = main.cpp 
SRC += Space.cpp
SRC += Field.cpp
SRC += Board.cpp
SRC += Bomb.cpp
SRC += Fire.cpp
SRC += Pie.cpp
SRC += Enemy.cpp
SRC += Wall.cpp
SRC += Player.cpp
SRC += GameLogic.cpp
OBJ = $(SRC:.cpp=.o)
BIN = $(PROJ).bin
CFLAGS =  -pedantic -std=c++11 -lncurses #-Wall
VOPT = --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes -v

.PHONY: default debug clean zip

default: clean $(BIN) debug 

debug: $(BIN)
	#@./$(BIN)
	@valgrind $(VOPT) ./$(BIN)

$(BIN): $(OBJ) 
	@echo "CC	$@"
	@$(CXX) $(CFLAGS) $^ -o $@

%.o: %.cpp 
	@echo "CC	$^"
	@$(CXX) $(CFLAGS) -c $^

zip:
	zip $(PROJ).zip *.cpp *.hpp makefile

clean: $(CLEAN)
	@echo "RM	*.o"
	@echo "RM	$(BIN)"
	@rm -f *.o $(BIN)
