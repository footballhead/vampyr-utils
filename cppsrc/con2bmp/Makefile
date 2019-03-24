CXXFLAGS = -O2 -Wall -std=c++17 -I..

LDFLAGS = -L../libvampyrtools -lvampyrtools

con2bmp: main.o ../libvampyrtools/libvampyrtools.a 
	$(CXX) main.o -o $@ $(LDFLAGS)

main.o: main.cpp ../libvampyrtools/con.hpp stb_image_write.h
	$(CXX) main.cpp -c -o main.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o con2bmp
