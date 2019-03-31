CXXFLAGS = -O2 -Wall -std=c++17 -fPIC

libvampyrtools.a: con.o image.o stb.o
	$(AR) rcs libvampyrtools.a con.o image.o stb.o

con.o: con.cpp con.hpp image.hpp
	$(CXX) con.cpp -c -o con.o $(CXXFLAGS)

image.o: image.cpp image.hpp
	$(CXX) image.cpp -c -o image.o $(CXXFLAGS)

stb.o: stb.cpp stb_image.h stb_image_write.h
	$(CXX) stb.cpp -c -o stb.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o *.a
