CXX = clang++
CXXFLAGS = -std=c++11 -Wsign-conversion -g
SRCOBJS = demo.o Complex.o
HEADERS = Tree.hpp Node.hpp Iterators.hpp Complex.hpp
TESTOBJS = Test.o TestCounter.o
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99
#
all: demo

demo: $(SRCOBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCOBJS)

demo.o: demo.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c demo.cpp

test: $(TESTOBJS) Complex.o
	$(CXX) $(CXXFLAGS) -o $@ $(TESTOBJS) Complex.o
	./$@

Complex.o: Complex.cpp Complex.hpp
	$(CXX) $(CXXFLAGS) -c Complex.cpp

Test.o: Test.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c Test.cpp

TestCounter.o: TestCounter.cpp
	$(CXX) $(CXXFLAGS) -c TestCounter.cpp

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

clean:
	rm -f demo test *.o