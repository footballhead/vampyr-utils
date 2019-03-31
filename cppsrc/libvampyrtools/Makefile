CXXFLAGS = -O2 -Wall -std=c++17 -fPIC

libvampyrtools.a: con.o image.o
	$(AR) rcs libvampyrtools.a con.o image.o

con.o: con.cpp con.hpp image.hpp
	$(CXX) con.cpp -c -o con.o $(CXXFLAGS)

image.o: image.cpp image.hpp
	$(CXX) image.cpp -c -o image.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o *.a
