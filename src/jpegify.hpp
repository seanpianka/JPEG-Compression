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
    Jpegify()
    {
    }
};

class Image
{
protected:
    struct Pixel
    {
    public:
        Pixel(uint8_t red   = 0,
              uint8_t green = 0,
              uint8_t blue  = 0,
              uint8_t alpha = 255)
        : red_(red), green_(green), blue_(blue), alpha_(alpha) {}

    private:
        uint8_t red_;
        uint8_t green_;
        uint8_t blue_;
        uint8_t alpha_;
    };
    std::unordered_map<std::string, uint16_t> properties;

public:
    Image(std::string filename = "")
    {
        width_ = 0;
        height_ = 0;

    }
    virtual ~Image() {}
    virtual bool load_from_file(std::string filename = "")=0;

protected:
    void read_bytes(uint16_t num_bytes, std::ifstream& fp,
                    uint16_t* store,    bool print = true)
    {
        for (uint16_t i = 1, byte = 0; i <= num_bytes; ++i)
        {
            byte = fp.get();
            if (print) printf("%x\t", byte);
            if (store) *store += byte;
        }
        if (print) printf("\n");
    }

    std::vector<std::vector<Pixel> > pixel_array_;
    uint16_t width_;
    uint16_t height_;
};

class BMP: public Image
{
public:
    BMP(std::string filename = "") : Image(filename)
    {
        properties["header_size"] = 0;
        properties["dib_header_size"] = 0;
        properties["bmp_header_size"] = 0;
        properties["bitmap_width"] = 0;
        properties["bitmap_height"] = 0;
        properties["color_planes"] = 0;
        properties["bits_per_pixel"] = 0;

        if (!filename.empty())
        {
            load_from_file(filename);
        }
    }

    bool load_from_file(std::string filename)
    {
        std::ifstream fp;
        fp.open(filename.c_str());
        if (!fp.is_open())
        {
            printf("Error opening image. Exiting.\n"); return false;
        }

        auto& props = properties;

        //=====================================================================
        // BMP Header
        //=====================================================================
        printf("\n::begin of BMP header (%d)::\n", props["bmp_header"]);

        // ID Field
        read_bytes(2, fp, NULL);

        // Size of the BMP file
        read_bytes(4, fp, NULL);

        // Application Specific
        read_bytes(2, fp, NULL);

        // Application Specific
        read_bytes(2, fp, NULL);

        // Offset where the pixel array (bitmap data) can be found
        read_bytes(4, fp, &props["header"]);

        printf("::end of BMP header::\n");

        //=====================================================================
        // DIB Header
        //=====================================================================
        // Number of bytes in the DIB header (from this point)
        props["dib_header"] = props["header"] - props["bmp_header"];

        printf("\n::begin of DIB header (%d)::\n", props["dib_header"]);

        // Number of bytes in the DIB header (from this point)
        read_bytes(4, fp, NULL);

        // Width of the bitmap in pixels
        read_bytes(4, fp, &props["bitmap_width"]);

        // Height of bitmap in pixels. Positive for bottom to top pixel order.
        read_bytes(4, fp, &props["bitmap_height"]);

        // Number of color planes being used
        read_bytes(2, fp, &props["color_planes_count"]);

        // Number of bits per pixel
        read_bytes(2, fp, &props["bits_per_pixel"]);

        // BI_RGB, no pixel array compression used
        read_bytes(4, fp, NULL);

        // Size of the raw bitmap data (including padding)
        read_bytes(4, fp, &props["pixel_array_size"]);

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
        if (props["dib_header"] > 40)
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

        if (props["dib_header"] > 108)
        {
            printf("Unknown file format. Exiting.\n");
        }

        printf("::end of DIB header::\n\n");

        printf("Bits per pixel: 0x%x\n", props["bits_per_pixel"]);
        printf("Color Planes: 0x%x\n", props["color_planes_count"]);
        printf("Bitmap Width: 0x%x\n", props["bitmap_width"]);
        printf("Bitmap Height: 0x%x\n", props["bitmap_height"]);

        printf("\n");

        //=====================================================================
        // Pixel Array
        //=====================================================================
        printf("::begin of pixel array (%d)::\n", props["pixel_array_size"]);

        for (uint8_t i = 0; i < props["pixel_array_size"]; i += 4)
        {
            read_bytes(4, fp, NULL);
        }

        printf("::end of pixel array::\n");

        fp.close();

        return true;
    }
};

};

#endif
