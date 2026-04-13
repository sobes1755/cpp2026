.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

SRCS = $(wildcard *.cpp)
BINS = $(SRCS:.cpp=)

.PHONY: all

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f $(BINS)
	rm -f hello.txt
