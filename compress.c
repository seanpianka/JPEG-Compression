#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const short IMAGE_WIDTH = 2;
const short IMAGE_HEIGHT = 2;

int read_bmp_bytes(unsigned char image[][3], const char* t_image_name);

int main()
{
    unsigned char image[IMAGE_WIDTH * IMAGE_HEIGHT][3];
    if (read_bmp_bytes(image, "colors.bmp") != 0)
    {
        printf("Failed to read byte data from BMP file. Exiting.\n");
        return 0;
    };

    return 0;
}

int read_bmp_bytes(unsigned char image[][3], const char* t_image_name)
{
    unsigned char byte = 0, header = 0, dib_header = 0, bmp_header = 14;
    FILE *fp;
    char* image_name = (char*)malloc((strlen(t_image_name) + 3) * sizeof(char*));
    strcpy(image_name, "./");
    strcat(image_name, t_image_name);

    //fp = fopen("./boat.bmp", "rb");
    fp = fopen(image_name, "rb");
    free(image_name);

    if (!fp) { printf("Error opening image. Exiting.\n"); return -1; }

    printf("\n::begin of BMP header (%d)::\n", bmp_header);
    for (int i = 1; i <= 2; ++i)
    { byte = getc(fp); printf("%x \t", byte); }
    printf("\n");

    for (int i = 1; i <= 4; ++i)
    { byte = getc(fp); printf("%x \t", byte); }
    printf("\n");

    for (int i = 1; i <= 4; ++i)
    { byte = getc(fp); printf("%x \t", byte); }
    printf("\n");

    for (int i = 1; i <= 4; ++i)
    { byte = getc(fp); printf("%x \t", byte); header += byte; }
    printf("\n::end of BMP header::\n");

    dib_header = header - bmp_header;
    printf("\n::begin of DIB header (%d)::\n", dib_header);
    for (int i = 1; i <= dib_header; ++i)
    {
        byte = getc(fp);
        printf("%x\t", byte);
        if (i % 4 ==0)
        {
            printf("\n");
        }
    }
    printf("::end of DIB header::\n\n");

    printf("Press enter to begin reading from pixel array...");
    getchar();

    for (int i = 0; i < 8; i++)
    {
        printf("[%d]:\t%x\t%x\t%x\n", i+1, getc(fp), getc(fp), getc(fp));
    }

    /*
    for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT * 50; ++i)
    {
        image[i][2] = getc(fp);
        image[i][1] = getc(fp);
        image[i][0] = getc(fp);
        printf("Pixel %d : [%x, %x, %x]\n", i+1,
                                            image[i][0],
                                            image[i][1],
                                            image[i][2]);
        //byte = getc(fp); byte = getc(fp); // ignore 4 byte padding (for now)

        if ((i+1) % 500 == 0)
        {
            printf("Press enter to begin reading pixels...");
            getchar();
        }
    }
    */

    fclose(fp);
    return 0;
}
