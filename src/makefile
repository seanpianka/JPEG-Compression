CPPFLAGS=--std=c++11 -Wall -Wextra
CPP=clang++

compress: compress.o
	$(CPP) $(CPPFLAGS) compress.o -o compress.x

compress.o: compress.cpp jpegify.hpp
	$(CPP) $(CPPFLAGS) -c compress.cpp

clean:
	rm -rf *.o compress.x
