CC              := gcc
CFLAGS 			:= -Wall -Werror -Wextra -std=c11
FUNC_DIR        := functions/
EXPRESSION_CALCULATOR_DIR			:= expression_calculator_backend/
FUNC_STACK_DIR		              := ${EXPRESSION_CALCULATOR_DIR}${FUNC_DIR}stack
FUNC_CALCULATION_DIR 			  := ${EXPRESSION_CALCULATOR_DIR}${FUNC_DIR}calculation
FUNC_CALCULATION_LIBRARY_DIR 	  := ${EXPRESSION_CALCULATOR_DIR}${FUNC_DIR}calculation_library
FUNC_EXPRESSION_TOKENIZER_DIR	  := ${EXPRESSION_CALCULATOR_DIR}${FUNC_DIR}expression_tokenizer
FUNC_SHUNTING_YARD_ALGORITHM_DIR  := ${EXPRESSION_CALCULATOR_DIR}${FUNC_DIR}shunting_yard_algorithm
FUNC_TEST_DIR   := tests/
OBJ_DIR         := ./
BUILD_DIR		:= ../build/
LIB_HEADER      := s21_calc_library.h
GCOV_FLAGS      := -fprofile-arcs -ftest-coverage
TEST_DIR_BUILD	:= tests/build/
LIB_STATIC      := s21_calc_library.a
VALGRIND_FLAGS  	:= --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log
QT_MAKEFILE  	:= QtMakefile.mk
DIST_DIR		:= ../archive

APP_DESTINATION	:= ./calculator_qmake.app/Contents/MacOS/
APP_NAME 		:= calculator_qmake

OS_NAME := $(shell uname -o 2>/dev/null || echo "Unknown")

OPEN_COMMAND := open

ifeq ($(OS_NAME), GNU/Linux)
    OPEN_COMMAND := xdg-open
	UBUNTU_FLAGS := -lrt -lsubunit $(shell pkg-config --cflags check) $(shell pkg-config --libs check)
	APP_DESTINATION:= ./
endif

TEST_FLAGS      := -lcheck -lm -lpthread $(UBUNTU_FLAGS)

FUNC_SRCS       := 	$(addprefix $(FUNC_CALCULATION_DIR)/, s21_calculation.c \
 															s21_calculation_handlers.c) \
					$(addprefix $(FUNC_EXPRESSION_TOKENIZER_DIR)/, s21_expression_tokenizer.c \
																	s21_validator.c) \
					$(addprefix $(FUNC_CALCULATION_LIBRARY_DIR)/, s21_calc_library.c) \
					$(addprefix $(FUNC_SHUNTING_YARD_ALGORITHM_DIR)/, s21_shunting_yard_algorithm.c) \
					$(addprefix $(FUNC_STACK_DIR)/, s21_stack.c) \

FUNC_OBJS_WITHOUT_OBJECT_DIRNAME = $(FUNC_SRCS:.c=.o)
FUNC_OBJS = $(subst $(FUNC_DIR), $(OBJ_DIR), $(FUNC_OBJS_WITHOUT_OBJECT_DIRNAME))

$(LIB_STATIC):$(FUNC_SRCS)
	mkdir ${EXPRESSION_CALCULATOR_DIR}tests/build
	$(CC) $(CFLAGS) -c $(FUNC_SRCS)
	ar -rcs $@ *.o
	make clean_obj

all: dvi rebuild test gcov_report install open_app style_check

build:
	make $(LIB_STATIC)

uninstall: clean
	-@rm -rf calculator_qmake.app
	-@rm -rf ./frontend/calculator_qmake.app

install: uninstall
	qmake -o ${QT_MAKEFILE} frontend/calculator_qmake.pro
	make -f ${QT_MAKEFILE}
	make -f ${QT_MAKEFILE} clean

open_app:
	$(APP_DESTINATION)$(APP_NAME)

dvi:
	$(OPEN_COMMAND) ../dvi-readme/README.html

rebuild: clean build

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cpp *.h ./*/*.cpp ./*/*.h ./*/*/*.cpp ./*/*/*.h

style_check:
	-@clang-format -n -style=Google  *.c *.h \
 									./*/*.c \
  									./*/*.h \
   									./*/*/*.c \
   									./*/*/*.h \
     								*.cpp \
      								./*/*.cpp \
       								./*/*/*.cpp
	-@echo "Style check finished"
style:
	-@clang-format -i -style=Google  *.c *.h \
 									./*/*.c \
  									./*/*.h \
   									./*/*/*.c \
   									./*/*/*.h \
     								*.cpp \
      								./*/*.cpp \
       								./*/*/*.cpp
	-@echo "Style apply finished"

gcov_report:
	mkdir ${EXPRESSION_CALCULATOR_DIR}report
	gcc ${EXPRESSION_CALCULATOR_DIR}${FUNC_TEST_DIR}main_test.c $(FUNC_SRCS) $(CFLAGS) $(TEST_FLAGS) $(GCOV_FLAGS) -o ./$@.out
	./$@.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

test: rebuild
	gcc ${EXPRESSION_CALCULATOR_DIR}${FUNC_TEST_DIR}main_test.c $(LIB_STATIC) $(CFLAGS) $(TEST_FLAGS)  -o ./test.out
	./test.out 2>&1 | tee test.log

test_valgrind:
	gcc tests/main_test.c $(LIB_STATIC) $(TEST_FLAGS) -o ./test.out
	valgrind $(VALGRIND_FLAGS) ./test.out

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

install_brew_goinfre: # be careful with this!
	cd ~/goinfre
	mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew

install_lcov:
	brew install lcov

install_qtcreator: #ubuntu root users only
	sudo apt update && sudo apt install qtcreator

clean:
	-@make clean_after_gcov
	-@rm -rf ${EXPRESSION_CALCULATOR_DIR}report
	-@rm -rf ${EXPRESSION_CALCULATOR_DIR}tests/build
	-@rm -rf moc_*.*
	-@rm -rf ./*/moc_*.*
	-@rm -rf ./*/*/moc_*.*
	-@rm -rf ${QT_MAKEFILE}
	-@rm -rf ./calculator_qmake.app
	-@rm -rf *.log
	-@rm -rf */*.log
	-@rm -rf */*/*.log
	-@rm -rf */*/*/*.log
	-@rm -rf ../*.log
	-@rm -rf ../*/*.log
	-@rm -rf ../*/*/*.log
	-@rm -rf ../*/*/*/*.log
	-@rm -rf */*.pro.user
	-@rm -rf *.pro.user
	-@rm -rf */ui_*.h
	-@rm -rf ui_*.h
	-@rm -rf .qtc_clangd
	-@rm -rf ./*/.qtc_clangd
	-@rm -rf ../*/.qtc_clangd
	-@rm -rf ../*/.qmake.stash
	-@rm -rf ./*/.qmake.stash
	-@rm -rf .qmake.stash
	-@rm -rf "__.SYMDEF SORTED"
	-@rm -rf ../*/*.o
	-@rm -rf ../*/*.out
	-@rm -rf ../*/*.info
	-@rm -rf ../*/*.a
	-@rm -rf ../*/*/*.o
	-@rm -rf ../*/*/*.out
	-@rm -rf ../*/*/*.info
	-@rm -rf ../*/*/*.a
	-@rm -rf ../*/*/*/*.o
	-@rm -rf ../*/*/*/*.out
	-@rm -rf ../*/*/*/*.info
	-@rm -rf ../*/*/*/*.a
	-@rm -rf ./object_files
	-@rm -rf ./tests/build
	-@rm -rf ./report
	-@rm -rf ./*.log
	-@rm -rf ../*/*.log
	-@rm -rf ../*.log
	-@echo "Clean finished"
dist: clean_dist
	mkdir ${DIST_DIR}
	cp -rf common ${DIST_DIR}
	cp -rf credit_calculator_backend ${DIST_DIR}
	cp -rf deposit_calculator_backend ${DIST_DIR}
	cp -rf expression_calculator_backend ${DIST_DIR}
	cp -rf frontend ${DIST_DIR}
	cp -rf develop ${DIST_DIR}
	cp -rf Makefile ${DIST_DIR}
	tar -zcvf ../archive.tar.gz ${DIST_DIR}
	make clean_dist

clean_dist:
	rm -rf ${DIST_DIR}
	rm -rf ../archive.tar


dev_%:
	make -f dev_Makefile.mk $@

clean_obj :
	-@rm -f *.o
	-@rm -f ./*/*.o
	-@rm -f ./*/*/*.o
	-@rm -f ./*/*/*/*.o

clean_after_gcov:
	-@rm -rf ../*.gc*
	-@rm -rf ../*/*.gc*
	-@rm -rf ../*/*/*.gc*
	-@rm -rf ../*/*/*/*.gc*
