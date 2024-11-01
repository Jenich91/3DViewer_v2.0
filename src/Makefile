.PHONY: all install uninstall tests gcov_report dist dvi linter cppcheck clang debug leaks clean
SHELL := /bin/bash

PROJECT_NAME = 3DViewer
INSTALL_PATH = ../Build
CC = g++
EXTRAWARN_FLAGS = -Wpedantic -Wshadow -Wuninitialized 
WARN_FLAGS= -Wall -Werror -Wextra
CFLAGS = -std=c++17 -lstdc++ $(WARN_FLAGS)
DEBUG_FLAG = -g
GCOVFLAG = --coverage
LDFLAGS = -lgtest
TEST_SRCS = tests.cc
MODEL_SRCS = Model/object.cc Model/matrix.cc Model/transform_matrix.cc
ALL_SRCS_FILES = find . -type f -name "*.cc" -name "*.cpp" -o -name "*.h"| grep -v "QtGifImage"
VERSION = v2_0
SCHOOL_PREFIX = s21_
FILENAME = "$(PROJECT_NAME)_$(VERSION)"
OS := $(shell uname)

openInstallDir:
ifeq ($(OS),Darwin)
ifeq (,$(wildcard !$(INSTALL_PATH)))
	open $(INSTALL_PATH)
endif
endif

all: install

# install and uninstall
install: clean
	mkdir -p $(INSTALL_PATH)/$(FILENAME); cd $(INSTALL_PATH)/$(FILENAME); qmake ../../src/$(FILENAME).pro; make; make clean; rm Makefile;
	make dvi
	make openInstallDir

uninstall:
	rm -rf $(INSTALL_PATH)/$(FILENAME)

# tests
tests: clean
	$(CC) $(MODEL_SRCS) $(LDFLAGS) tests.cc -o tests.out
	./tests.out

gcov_report: clean
	$(CC) $(CFLAGS) $(TEST_SRCS) $(MODEL_SRCS) $(LDFLAGS) $(GCOVFLAG) -o gcov_rep.out
	./gcov_rep.out
	lcov -t "gcov_rep" --no-external --output-file=coverag.info --capture --directory .
	genhtml -o ./report coverag.info

# dist
dist: install dvi
	cd $(INSTALL_PATH); tar -cvzf $(FILENAME).tar.gz ./$(FILENAME);
	make openInstallDir

# dvi
dvi:
	mkdir -p $(INSTALL_PATH)/$(FILENAME)/
	cd $(INSTALL_PATH)/$(FILENAME); makeinfo --html --no-split --force ../../src/etc/Documentation.texi -o ./README.html

# style && cppcheck
cppcheck:
	$(ALL_SRCS_FILES) | xargs cppcheck --enable=unusedFunction --enable=all --language=c++ --std=c++17 --suppress=unusedStructMember --suppress=missingInclude --suppress=unusedFunction

clang:
	@cp -a ../materials/linters/.clang-format .clang-format

	@clang-format -i Model/*
	@clang-format -i Controller/*
	@clang-format -i View/adapter.*
	@clang-format -i View/view.*   
	@clang-format -i View/settings.*
	@clang-format -i View/main.cpp  
	@clang-format -i View/glwidget.*
	@clang-format -i View/geometryengine.*
	@clang-format -i tests.cc

	clang-format -n Model/*
	clang-format -n Controller/*
	clang-format -n View/*
	clang-format -n tests.cc

	@rm -f .clang-format

# leaks check
debug: clean
	$(CC) $(CFLAGS) $(TEST_SRCS) $(LIB_NAME) -I./ -L./ $(LDFLAGS) $(MODEL_SRCS) -o debug.out -ggdb3

leaks: debug
ifeq ($(OS), Darwin)
	leaks --atExit -- ./debug.out -exclude
else
	valgrind -q --tool=memcheck --leak-check=full --leak-resolution=med ./debug.out
endif

# clean
clean:
	qmake $(FILENAME).pro -o Qmakefile
	make -f Qmakefile clean
	rm -rf *.o *.a *.gcno test ./report ./*.dSYM *.out *.gcda gcov_report *.info clang-format *.user .qmake.stash *.dSYM *.tmp CPPLINT.cfg Qmakefile
	find . -name .DS_Store -print0 | xargs -0 git rm -f --ignore-unmatch
