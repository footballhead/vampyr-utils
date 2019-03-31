CXXFLAGS = -O2 -Wall -std=c++17 -I..

LDFLAGS = -L../libvampyrtools -lvampyrtools -L../stb -lstb

bmp2con: main.o ../libvampyrtools/libvampyrtools.a ../stb/libstb.a
	$(CXX) main.o -o $@ $(LDFLAGS)

main.o: main.cpp ../libvampyrtools/image.hpp ../stb/stb_image.h
	$(CXX) main.cpp -c -o main.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o bmp2con
