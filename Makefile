CXXFLAGS=-g -O0 -Wall -I.
all: example
example: example.cpp rational/gcd.hpp rational/math.hpp rational/rational.hpp rational/reduce.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<
clean:
	rm -f example *~
