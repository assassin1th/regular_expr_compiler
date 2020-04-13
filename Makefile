BIN_DIR = bin/
CPP_DIR = cpp/
CPP_SRC_DIR = $(CPP_DIR)src/
CPP_INC_DIR = $(CPP_DIR)include/
FLAGS = -I$(CPP_INC_DIR) -std=c++17
CXX = g++

DEPS = $(BIN_DIR)AST.o\
       $(BIN_DIR)compiler.o\
	   $(BIN_DIR)token_stream.o\
	   $(BIN_DIR)parser.o\
	   $(BIN_DIR)state.o

EXAMPLES_DIR = examples/
EXAMPLES_BIN_DIR = $(EXAMPLES_DIR)bin/
USAGE_EXAMPLE = $(EXAMPLES_DIR)simple_usage.out
EXAMPLES_SRC_DIR = $(EXAMPLES_DIR)sources/

EXAMPLE_SIMPLE_USAGE_DEPS = $(EXAMPLES_BIN_DIR)main.o

EXAMPLES_DEPS = $(DEPS)\
				$(EXAMPLE_SIMPLE_USAGE_DEPS)

EXAMPLES_FLAGS = $(FLAGS)

$(BIN_DIR)%.o : $(CPP_SRC_DIR)%.cpp
	$(CXX) -c $^ $(FLAGS) -o $@

$(EXAMPLES_BIN_DIR)%.o : $(EXAMPLES_SRC_DIR)%.cpp
	$(CXX) -c $^ $(EXAMPLES_FLAGS) -o $@

$(USAGE_EXAMPLE) : $(EXAMPLES_DEPS)
	$(CXX) $^ -o $@

main: $(DEPS)
	touch main
