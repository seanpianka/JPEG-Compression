#ifndef PIANKA_JPEGIFY_HPP
#define PIANKA_JPEGIFY_HPP

#include <vector>
#include <string>
#include <array>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <unordered_map>

namespace seanpianka
{

class Jpegify
{
public:
    Jpegify();
}

class Image
{
public:
    struct Pixel
    {
    public:
        Pixel(uint8_t red   = 0,
              uint8_t green = 0,
              uint8_t blue  = 0,
              uint8_t alpha = 255)
        : red_(red), green_(green), blue_(blue_), alpha_(alpha) {}

    private:
        uint8_t red_;
        uint8_t green_;
        uint8_t blue_;
        uint8_t alpha_;
    }

public:
    Image(std::string filename = "")
    {

    }
    virtual ~Image();
    bool load_from_file(std::string filename = "");

protected:
    std::vector<std::vector<Pixel>> pixel_array_;
    uint16_t width_;
    uint16_t height_;
};

class BMP: public Image
{
public:
    bool load_from_file(std::string filename = "")
    {
    }

    BMP(std::string filename = "") : Image(filename),
    {
        uint8_t header = 0,
                dib_header = 0,
                bmp_header = 14,
                bitmap_width = 0,
                bitmap_height = 0,
                color_planes_count = 0,
                bits_per_pixel = 0;

        std::istream fp(filename);
        if (!fp.is_open())
        {
            printf("Error opening image. Exiting.\n"); return -1;
        }

        //=====================================================================
        // BMP Header
        //=====================================================================
        printf("\n::begin of BMP header (%d)::\n", bmp_header);

        // ID Field
        read_bytes(2, fp, NULL);

        // Size of the BMP file
        read_bytes(4, fp, NULL);

        // Application Specific
        read_bytes(2, fp, NULL);

        // Application Specific
        read_bytes(2, fp, NULL);

        // Offset where the pixel array (bitmap data) can be found
        read_bytes(4, fp, &header);

        printf("::end of BMP header::\n");

        //=========================================================================
        // DIB Header
        //=========================================================================
        // Number of bytes in the DIB header (from this point)
        dib_header = header - bmp_header;

        printf("\n::begin of DIB header (%d)::\n", dib_header);

        // Number of bytes in the DIB header (from this point)
        read_bytes(4, fp, NULL);

        // Width of the bitmap in pixels
        read_bytes(4, fp, &bitmap_width);

        // Height of the bitmap in pixels. Positive for bottom to top pixel order.
        read_bytes(4, fp, &bitmap_height);

        // Number of color planes being used
        read_bytes(2, fp, &color_planes_count);

        // Number of bits per pixel
        read_bytes(2, fp, &bits_per_pixel);

        // BI_RGB, no pixel array compression used
        read_bytes(4, fp, NULL);

        // Size of the raw bitmap data (including padding)
        read_bytes(4, fp, &pixel_array_size);

        // Print resolution of the image
        // Pixels/meter horizontal
        read_bytes(4, fp, NULL);
        // Pixels/meter vertical
        read_bytes(4, fp, NULL);

        // Number of colors in the palette
        read_bytes(4, fp, NULL);

        // Number of *important* colors in the palette
        // 0 means all colors are important
        read_bytes(4, fp, NULL);

        // for 32-bit RGB bmp files
        if (dib_header > 40)
        {
            // Red channel bit mask (valid because BI_BITFIELDS is specified)
            read_bytes(4, fp, NULL);
            // Green channel bit mask (valid because BI_BITFIELDS is specified)
            read_bytes(4, fp, NULL);
            // Blue channel bit mask (valid because BI_BITFIELDS is specified)
            read_bytes(4, fp, NULL);
            // Alpha channel bit mask
            read_bytes(4, fp, NULL);
            // LCS_WINDOWS_COLOR_SPACE
            read_bytes(4, fp, NULL);
            // Color space endpoints, unused for LCS "Win" or "sRGB"
            read_bytes(36, fp, NULL);
            // 0 Red Gamma, unused for LCS "Win" or "sRGB"
            read_bytes(4, fp, NULL);
            // 0 Green Gamma, unused for LCS "Win" or "sRGB"
            read_bytes(4, fp, NULL);
            // 0 Blue Gamma, unused for LCS "Win" or "sRGB"
            read_bytes(4, fp, NULL);
        }

        if (dib_header > 108)
        {
            printf("Unknown file format. Exiting.\n");
        }

        printf("::end of DIB header::\n\n");

        printf("Bits per pixel: 0x%x\n", bits_per_pixel);
        printf("Color Planes: 0x%x\n", color_planes_count);
        printf("Bitmap Width: 0x%x\n", bitmap_width);
        printf("Bitmap Height: 0x%x\n", bitmap_height);

        printf("\n");

        //=========================================================================
        // Pixel Array
        //=========================================================================
        printf("::begin of pixel array (%d)::\n", pixel_array_size);

        for (uint8_t i = 0; i < pixel_array_size; i += 4)
        {
            read_bytes(4, fp, NULL);
        }

        printf("::end of pixel array::\n");
    }

}

protected:
    void read_bytes(const uint8_t& num_bytes, std::istream& fp, uint8_t* storage)
    {
        uint8_t byte;
        for (uint8_t i = 1; i <= num_bytes; ++i)
        { byte = getc(fp); printf("%x \t", byte); if (storage) *storage += byte; }
        printf("\n");
    }

    std::unordered_map<std::string, uint8_t> properties;
};

#endif
