CXXFLAGS = -O2 -Wall -std=c++17 -I..

LDFLAGS = -L../libvampyrtools -lvampyrtools -L../stb -lstb -lstdc++fs

splitss: main.o ../libvampyrtools/libvampyrtools.a ../stb/libstb.a
	$(CXX) main.o -o $@ $(LDFLAGS)

main.o: main.cpp ../stb/stb_image.h ../stb/stb_image_write.h ../libvampyrtools/image.hpp
	$(CXX) main.cpp -c -o main.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o splitss
