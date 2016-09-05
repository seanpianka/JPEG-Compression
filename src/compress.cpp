#include <iostream>
#include <cstdlib>
#include "jpegify.hpp"


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Incorrect usage. ./compress.x [FILENAME]. Exiting.\n";
        std::exit(1);
    }

    seanpianka::BMP img{"colors2.bmp"};
    //img.compress();
    //img.output("colors2.jpg");

    return 0;
}
