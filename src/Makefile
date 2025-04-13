CC=g++
FLAGS  = -Wall -Werror -Wextra -std=c++17
SOURCE = *.cc

ifeq ($(shell uname -s),Linux)
	LIBS=-lm -lgtest -lgmock -pthread
endif

ifeq ($(shell uname -s),Darwin)
	LIBS=-lgtest -lgmock -pthread
endif

all: matrix_oop.a test

matrix_oop.a:
	$(CC) $(FLAGS) -c $(SOURCE) $(LIBS)
	ar rcs matrix_oop.a *.o
	@rm -rf *.o

test : matrix_oop.a
	$(CC) tests/*.cc $(SOURCE) $(LIBS)  -lm -o  matrix_oop_test
	./matrix_oop_test

clean :
	@rm -rf test
	@rm -rf *.a
	@rm -rf *.gcno
	@rm -rf *.gcda *.o
	@rm -rf *.html
	@rm -rf *.info
	@rm -rf *.css
	@rm -rf report
	@rm -rf report_files
	@rm -rf test.dSYM
	@rm -rf a.out
	@rm -rf *.gcov
	@rm matrix_oop_test

clang_format:
	@clang-format -style=Google -i *.cc *.h
	@clang-format -style=Google -i  tests/*.cc

style:
	@clang-format -style=Google -n *.cc
	@clang-format -style=Google -n  tests/*.cc


.PHONY: clean
