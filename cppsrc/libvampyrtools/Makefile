CXXFLAGS = -O2 -Wall -std=c++17 -fPIC

libvampyrtools.a: con.o
	$(AR) rcs libvampyrtools.a con.o

con.o: con.cpp con.hpp
	$(CXX) con.cpp -c -o con.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o libvampyrtools.a
