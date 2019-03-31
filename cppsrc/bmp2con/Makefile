CXXFLAGS = -O2 -Wall -std=c++17 -I..

LDFLAGS = -L../libvampyrtools -lvampyrtools

bmp2con: main.o ../libvampyrtools/libvampyrtools.a
	$(CXX) main.o -o $@ $(LDFLAGS)

main.o: main.cpp ../libvampyrtools/image.hpp ../libvampyrtools/stb_image.h
	$(CXX) main.cpp -c -o main.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o bmp2con
