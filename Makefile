CXX = clang++
CXXFLAGS = -std=c++11 -Wsign-conversion -g
SRCOBJS = demo.o
TESTOBJS = Test.o TestCounter.o
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99
#
all: demo

demo: $(SRCOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCOBJS)

demo.o: demo.cpp Tree.hpp
	$(CXX) $(CXXFLAGS) -c demo.cpp

test: $(TESTOBJS) Tree.hpp
	$(CXX) $(CXXFLAGS) -o $@ $(TESTOBJS)
	./$@

Test.o: Test.cpp
	$(CXX) $(CXXFLAGS) -c Test.cpp

TestCounter.o: TestCounter.cpp
	$(CXX) $(CXXFLAGS) -c TestCounter.cpp

clean:
	rm -f demo test *.o