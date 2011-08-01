CXXFLAGS=-g -O0 -Wall
all: example
example: example.cpp prime.hpp  rational_algo.hpp  rational.hpp  reduce.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<
clean:
	rm -f example *~
