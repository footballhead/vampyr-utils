CXXFLAGS = -O2 -Wall -std=c++17 -I..

LDFLAGS = -L../vampyrutils -lvampyrutils

con2bmp: main.o ../vampyrutils/libvampyrutils.a
	$(CXX) main.o -o $@ $(LDFLAGS)

main.o: main.cpp ../vampyrutils/con2bmp.hpp
	$(CXX) main.cpp -c -o main.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o con2bmp
