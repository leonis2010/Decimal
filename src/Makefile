.PHONY: s21_decimal.a test gcov_report check rebuild clean
CC = gcc -g -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
LIBS=-lcheck
LINUX=-lcheck -lm -lpthread -lrt -lsubunit
HEADERS = s21_decimal.h
SUBDIRS = arithmetic_operators common comparison_operators converters other_functions
SOURCES = $(foreach dir, $(SUBDIRS), $(wildcard $(dir)/*.c))
TEST_SOURCE=$(shell find tests -type f -name '*.c')
TEST=$(filter-out tests/main_test.c, $(TEST_SOURCE))

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES))
ifeq ($(OS), Linux)
 CC += -D OS_LINUX # 654 737
endif
ifeq ($(OS), Darwin)
 CC += -D OS_MAC
endif

%.o: %.c $(HEADER)
	$(CC)  -c $< -o $@

all: s21_decimal.a

show: test
	echo "$(TEST)"
	# cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCES)
	#CK_FORK=no valgrind -s  --trace-children=yes --track-origins=yes --track-fds=yes --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file=RESULT_VALGRIND.txt $(SOURCES)
	valgrind --leak-check=yes --log-file="./report.log" ./test.out
s21_decimal.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_decimal.a $(OBJ_LIBRARY)
	ranlib s21_decimal.a
	find . -type f \( -name "*.o" \) -exec rm -f {} \;

test: clean s21_decimal.a tests/test.c
ifeq ($(OS), Darwin)
	$(CC)  $(TEST) s21_decimal.a -o test.out $(LIBS)
else
	$(CC)  $(TEST) s21_decimal.a -o test.out $(LINUX)
endif
	./test.out


gcov_report: s21_decimal.a tests/test.c
ifeq ($(OS), Darwin)
	gcc $(GCOVFLAGS) $(TEST) $(SOURCES)  -o report.out $(LIBS)
else
	gcc $(GCOVFLAGS) $(TEST) $(SOURCES)  -o report.out $(LINUX)
endif
	./report.out
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o report/ Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html


check:
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} \;

rebuild: clean all

clean:
	find . -type f \( -name "*.o" -o -name "*.a" -o -name "*.gcno" -o -name "*.gcda" -o -name "*.info" -o -name "*.out" -o -name "*.gcov" -o -name "*.log" \) -exec rm -f {} \;
	rm -rf ./report
	rm -rf *.dSYM
