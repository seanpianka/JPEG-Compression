#include <iostream>
#include "jpegify.hpp"


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Incorrect usage. ./compress.x [FILENAME]. Exiting.\n";
    }

    pianka::BMP img("colors2.bmp");
    img.compress();
    img.output("colors2.jpg");
}
