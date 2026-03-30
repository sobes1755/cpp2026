.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -I./include/
LDLIBS = -ltbb

SRCS = $(wildcard *.cpp)
BINS = $(SRCS:.cpp=)

.PHONY: all

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

.PHONY: clean

clean:
	rm -f $(BINS)
