CXXFLAGS = -O0 -g -Wall -std=c++17 -I..

LDFLAGS = -L../vampyrutils -lvampyrutils

map_layer_enconter: main.o ../vampyrutils/libvampyrutils.a
	$(CXX) main.o -o $@ $(LDFLAGS)

main.o: main.cpp ../vampyrutils/csv.hpp ../vampyrutils/image.hpp
	$(CXX) main.cpp -c -o main.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o map_layer_enconter
