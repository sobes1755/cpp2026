.POSIX:

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O3

SRCS = $(wildcard *.cpp)
BINS = $(SRCS:.cpp=)

.PHONY: all

all: $(BINS)

leak: leak.cpp
	$(CXX) $< -o $@ -Wall -Wextra -Werror -std=c++23 -O0 -fsanitize=leak

vptr: vptr.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -Wno-invalid-offsetof -Wno-pmf-conversions

catbarks: catbarks.cpp
	$(CXX) $< -o $@ -Wall -Wextra -Werror -std=c++23 -O1

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f $(BINS)
