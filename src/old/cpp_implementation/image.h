#ifndef _COMPRESS_IMAGE_
#define _COMPRESS_IMAGE_

#include <cstdint>
#include <array>
#include <vector>

namespace Jpegify
{
    class Image
    {
    public:
        Image();
        ~Image();
    private:
        std::vector<> pixel_array_;
        uint8_t width_;
        uint8_t height_;
    };
};

#endif
