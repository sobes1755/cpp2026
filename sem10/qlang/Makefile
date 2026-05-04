.POSIX:

# ANother Tool for Language Recognition
# https://www.antlr.org/
#
# sudo apt update
# sudo apt install antlr4
# sudo apt install libantlr4-runtime-dev

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -O3 -I/usr/include/antlr4-runtime
LDFLAGS = -lantlr4-runtime

ANTLR_FLAGS = -Wno-deprecated-declarations -Wno-tautological-compare -Wno-overloaded-virtual -Wno-attributes -Wno-unused-parameter

ANTLR_CPP = QuaternionLexer.cpp QuaternionParser.cpp QuaternionBaseVisitor.cpp QuaternionVisitor.cpp
ANTLR_H = QuaternionLexer.h QuaternionParser.h QuaternionBaseVisitor.h QuaternionVisitor.h

.PHONY: all run clean

all: qlang

qlang: qlang.cpp qlang.h qeval.h qgeom.h $(ANTLR_CPP) $(ANTLR_H)
	$(CXX) $(CXXFLAGS) $(ANTLR_FLAGS) $^ $(LDFLAGS) -o $@

$(ANTLR_CPP) $(ANTLR_H): Quaternion.g4
	antlr4 -Dlanguage=Cpp -visitor -no-listener Quaternion.g4

run:
	./qlang a.q
	./qlang b.q

clean:
	rm -f ./qlang $(ANTLR_CPP) $(ANTLR_H) *.tokens *.interp
