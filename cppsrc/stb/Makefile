CXXFLAGS = -O2 -Wall -std=c++17 -fPIC

libstb.a: stb.o
	$(AR) rcs libstb.a stb.o

stb.o: stb.cpp stb_image.h stb_image_write.h
	$(CXX) stb.cpp -c -o stb.o $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) *.o *.a
