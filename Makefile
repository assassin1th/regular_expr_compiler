BIN_DIR = bin/
CPP_DIR = cpp/
CPP_SRC_DIR = $(CPP_DIR)src/
CPP_INC_DIR = $(CPP_DIR)include/
FLAGS = -I$(CPP_INC_DIR) -std=c++17
CXX = g++

DEPS = $(BIN_DIR)AST.o\
       $(BIN_DIR)compiler.o\
	   $(BIN_DIR)lexer.o\
	   $(BIN_DIR)parser.o\
	   $(BIN_DIR)state.o

$(BIN_DIR)%.o : $(CPP_SRC_DIR)%.cpp
	$(CXX) -c $^ $(FLAGS) -o $@

main: $(DEPS)
	touch main
