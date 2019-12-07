# This makefile was generated using a template provided from 
# Harlan James <waldroha@oregonstate.edu>
#
PROJ = AmazonFireGame
$(CXX) = g++
SRC = main.cpp 
SRC += Space.cpp
SRC += Field.cpp
SRC += Tree.cpp
SRC += Board.cpp
SRC += Box.cpp
SRC += Player.cpp
SRC += TestSpace.cpp  #delete this
SRC += GameLogic.cpp
OBJ = $(SRC:.cpp=.o)
BIN = $(PROJ).bin
CFLAGS =  -pedantic -std=c++11 -lncurses #-Wall
VOPT = --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes

.PHONY: default debug clean zip

default: clean $(BIN) #debug

debug: $(BIN)
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
