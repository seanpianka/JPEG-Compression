#include <stdio.h>
#include <stdlib.h>

const short IMAGE_WIDTH = 800;
const short IMAGE_HEIGHT = 600;

int main()
{
    unsigned char image[IMAGE_WIDTH * IMAGE_HEIGHT][3];
    unsigned char byte = 0, header = 0, dib_header = 0, bmp_header = 14;
    FILE *fp;

    //fp = fopen("./boat.bmp", "rb");
    fp = fopen("./field.bmp", "rb");
    if (!fp) { printf("Error opening image. Exiting.\n"); exit(0); }

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
    printf("\n::end of BMP header::\n\n");

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

    for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; ++i)
    {
        image[i][2] = getc(fp);
        image[i][1] = getc(fp);
        image[i][0] = getc(fp);
        printf("Pixel %d : [%x, %x, %x]\n", i+1,
                                            image[i][0],
                                            image[i][1],
                                            image[i][2]);
        byte = getc(fp); byte = getc(fp); // ignore 4 byte padding (for now)

        if ((i+1) % 500 == 0)
        {
            printf("Press enter to begin reading pixels...");
            getchar();
        }
    }

    fclose(fp);

    return 0;
}
