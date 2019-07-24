TEST_CPP_SRC_DIR			= test/cpp/src/
COMP_CPP_SRC_DIR			= compiler/cpp/src/


FLAGS						= \
								-I$(TEST_CPP_SRC_DIR)../include/\
								-I$(COMP_CPP_SRC_DIR)../include/\
								-I.\

SRC 						=	\
								$(COMP_CPP_SRC_DIR)lex.o

ifdef __TEST__
FLAGS						+= \
								-D__DEBUG__
TARGET 						=	test.out

SRC 						+=	\
								$(TEST_CPP_SRC_DIR)test.o
else
endif

%.o : %.cpp
	g++ -c $^ -o $@ $(FLAGS)

%.o : %.c
	gcc -c $^ -o $@ $(FLAGS)

$(TARGET) : $(SRC)
	g++ $^ -o $@

.PHONY : clean

clean :
	rm -rf $(SRC)
