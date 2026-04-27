.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O3

SRCS = $(wildcard *.cpp)
BINS = $(SRCS:.cpp=)

.PHONY: all

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

pdf: *.tex
	lualatex nfa.tex

clean:
	rm -f $(BINS)
	rm -f *.log
	rm -f *.aux
