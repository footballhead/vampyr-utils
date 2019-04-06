CXXFLAGS = -O2 -Wall -std=c++17 -I..

LDFLAGS = -L../vampyrutils -lvampyrutils

map2bmp: main.o ../vampyrutils/libvampyrutils.a
	$(CXX) main.o -o $@ $(LDFLAGS)

main.o: main.cpp ../vampyrutils/image.hpp ../vampyrutils/io.hpp
	$(CXX) main.cpp -c -o main.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o map2bmp
