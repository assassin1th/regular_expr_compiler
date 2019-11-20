FLAGS			= \
			-I $(INCLUDE_DIR)
TEST_FLAGS		= \
			$(FLAGS)\
			-D TEST
BIN_DIR			= bin/
SRC_DIR			= src/
C_SRC_DIR		= $(SRC_DIR)c/
INCLUDE_DIR		= src/include/
TEST_DIR		= test/
TESTS_DIR		= $(TEST_DIR)tests/
LEXER_TESTS_DIR		= $(TESTS_DIR)lexer/
TEST_BIN_DIR		= $(TEST_DIR)bin/
TEST_LEXER		= $(TEST_BIN_DIR)lexer
TEST_LEXER_DEPS		= \
				$(TEST_BIN_DIR)lexer.o

TEST_SYM_SET		= $(TEST_BIN_DIR)sym_set
TEST_SYM_SET_DEPS	= \
				$(TEST_BIN_DIR)sym_set.o
TEST_STATE_SET		= $(TEST_BIN_DIR)state_set
TEST_STATE_SET_DEPS	= \
				$(TEST_BIN_DIR)state_set.o

$(TEST_SYM_SET): $(TEST_SYM_SET_DEPS)
	gcc $^ -o $@
$(TEST_LEXER): $(TEST_LEXER_DEPS)
	gcc $^ -o $@
$(TEST_STATE_SET): $(TEST_STATE_SET_DEPS)
	gcc $^ -o $@

$(TEST_BIN_DIR)%.o: $(C_SRC_DIR)%.c
	gcc -c $^ -o $@ $(TEST_FLAGS)

$(BIN_DIR)%.o: $(C_SRC_DIR)%.c
	gcc -c $^ -o $@ $(FLAGS)

.PHONY: test clean

test: $(TEST_LEXER) $(TEST_SYM_SET) $(TEST_STATE_SET)
	./$(TEST_DIR)run_tests.sh lexer
	./$(TEST_DIR)run_tests.sh sym_set
	./$(TEST_DIR)run_tests.sh state_set

clean:
	rm -rf $(TEST_BIN_DIR)*
	rm -rf $(BIN_DIR)*
