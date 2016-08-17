#ifndef PIANKA_JPEGIFY_HPP
#define PIANKA_JPEGIFY_HPP

#include <vector>
#include <string>
#include <array>
#include <cstdint>
#include <iostream>
#include <fstream>

namespace pianka
{

class Jpegify
{
public:
    Jpegify();
}

class Image
{
protected:
    struct Pixel
    {
        Pixel(uint8_t red   = 0,
              uint8_t green = 0,
              uint8_t blue  = 0,
              uint8_t alpha = 255)
        : red_(red), green_(green), blue_(blue_), alpha_(alpha) {}
        uint8_t red_;
        uint8_t green_;
        uint8_t blue_;
        uint8_t alpha_;
    }

public:
    Image(std::string filename = "")=0;
    bool load_from_file(std::string filename = "");
protected:
    std::vector<std::vector<Pixel>> pixel_array_;
    uint16_t width_;
    uint16_t height_;
};

class

};

#endif
