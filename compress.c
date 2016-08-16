#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const short IMAGE_WIDTH = 2;
const short IMAGE_HEIGHT = 2;
const char* IMAGE_NAME = "colors2.bmp";
//const char* IMAGE_NAME = "boat.bmp";

int read_bmp_bytes(unsigned char image[][3], const char* t_image_name);

int main()
{
    unsigned char image[IMAGE_WIDTH * IMAGE_HEIGHT][3];
    if (read_bmp_bytes(image, IMAGE_NAME) != 0)
    {
        printf("Failed to read byte data from BMP file. Exiting.\n");
        return 0;
    };

    return 0;
}

void read_bytes(unsigned int num_bytes, FILE* fp, unsigned int* storage)
{
    unsigned int byte;
    for (unsigned int i = 1; i <= num_bytes; ++i)
    { byte = getc(fp); printf("%x \t", byte); if (storage) *storage += byte; }
    printf("\n");
}

int read_bmp_bytes(unsigned char image[][3], const char* t_image_name)
{
    unsigned char header = 0,
                  dib_header = 0,
                  bmp_header = 14,
                  bitmap_width = 0,
                  bitmap_height = 0,
                  color_planes_count = 0,
                  bits_per_pixel = 0;
    unsigned int pixel_array_size = 0;

    char* image_name = (char*)malloc((strlen(t_image_name) + 3) * sizeof(char));
    strcpy(image_name, "./");
    strcat(image_name, t_image_name);

    FILE *fp = fopen(image_name, "rb");
    free(image_name);
    if (!fp) { printf("Error opening image. Exiting.\n"); return -1; }

    //=========================================================================
    // BMP Header
    //=========================================================================
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

    for (int i = 0; i < pixel_array_size; i += 4)
    {
        read_bytes(4, fp, NULL);
    }

    printf("::end of pixel array::\n");

    fclose(fp);
    return 0;
}
