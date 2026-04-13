.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++26

SRCS = $(wildcard *.cpp)
BINS = $(SRCS:.cpp=)

.PHONY: all

all: $(BINS)

trace: trace.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -lstdc++exp

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f $(BINS)
