CXXFLAGS = -O2 -Wall -std=c++17 -I..

LDFLAGS = -L../libvampyrtools -lvampyrtools -lstdc++fs

splitss: main.o ../libvampyrtools/libvampyrtools.a
	$(CXX) main.o -o $@ $(LDFLAGS)

main.o: main.cpp ../libvampyrtools/stb_image.h ../libvampyrtools/stb_image_write.h ../libvampyrtools/image.hpp
	$(CXX) main.cpp -c -o main.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o splitss
