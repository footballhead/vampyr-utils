CXXFLAGS = -O2 -Wall -std=c++17 -fPIC

libvampyrutils.a: bmp2con.o color.o con2bmp.o image.o io.o math.o stb.o
	$(AR) rcs libvampyrutils.a bmp2con.o color.o con2bmp.o image.o io.o math.o stb.o

bmp2con.o: bmp2con.cpp bmp2con.hpp image.hpp
	$(CXX) bmp2con.cpp -c -o bmp2con.o $(CXXFLAGS)

color.o: color.cpp color.hpp
	$(CXX) color.cpp -c -o color.o $(CXXFLAGS)

con2bmp.o: con2bmp.cpp con2bmp.hpp image.hpp
	$(CXX) con2bmp.cpp -c -o con2bmp.o $(CXXFLAGS)

image.o: image.cpp image.hpp color.hpp math.hpp
	$(CXX) image.cpp -c -o image.o $(CXXFLAGS)

io.o: io.cpp io.hpp
	$(CXX) io.cpp -c -o io.o $(CXXFLAGS)

math.o: math.cpp math.hpp
	$(CXX) math.cpp -c -o math.o $(CXXFLAGS)

stb.o: stb.cpp stb_image.h stb_image_write.h
	$(CXX) stb.cpp -c -o stb.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o *.a
