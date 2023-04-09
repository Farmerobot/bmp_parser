#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

// https://docs.microsoft.com/pl-pl/previous-versions/dd183376(v=vs.85)
typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

void read_bmp(FILE *bmp_file, BITMAPFILEHEADER *file_header, BITMAPINFOHEADER *info_header, unsigned char **pixel_data)
{
    fread(&file_header->bfType, sizeof(file_header->bfType), 1, bmp_file);
    fread(&file_header->bfSize, sizeof(file_header->bfSize), 1, bmp_file);
    fread(&file_header->bfReserved1, sizeof(file_header->bfReserved1), 1, bmp_file);
    fread(&file_header->bfReserved2, sizeof(file_header->bfReserved2), 1, bmp_file);
    fread(&file_header->bfOffBits, sizeof(file_header->bfOffBits), 1, bmp_file);
    fread(&info_header->biSize, sizeof(info_header->biSize), 1, bmp_file);
    fread(&info_header->biWidth, sizeof(info_header->biWidth), 1, bmp_file);
    fread(&info_header->biHeight, sizeof(info_header->biHeight), 1, bmp_file);
    fread(&info_header->biPlanes, sizeof(info_header->biPlanes), 1, bmp_file);
    fread(&info_header->biBitCount, sizeof(info_header->biBitCount), 1, bmp_file);
    fread(&info_header->biCompression, sizeof(info_header->biCompression), 1, bmp_file);
    fread(&info_header->biSizeImage, sizeof(info_header->biSizeImage), 1, bmp_file);
    fread(&info_header->biXPelsPerMeter, sizeof(info_header->biXPelsPerMeter), 1, bmp_file);
    fread(&info_header->biYPelsPerMeter, sizeof(info_header->biYPelsPerMeter), 1, bmp_file);
    fread(&info_header->biClrUsed, sizeof(info_header->biClrUsed), 1, bmp_file);
    fread(&info_header->biClrImportant, sizeof(info_header->biClrImportant), 1, bmp_file);

    // *pixel_data = malloc(info_header->biSizeImage);

    // if (pixel_data == NULL)
    // {
    //     printf("Error allocating memory");
    // }
    // fread(pixel_data, info_header->biSizeImage, 1, bmp_file);
    // fclose(bmp_file);
}

void print_bmp(BITMAPFILEHEADER *file_header, BITMAPINFOHEADER *info_header)
{
    printf("BITMAPFILEHEADER:\n");
    printf("  bfType:          0x%x (BM)\n", file_header->bfType);
    printf("  bfSize:          %d\n", file_header->bfSize);
    printf("  bfReserved1:     0x%x\n", file_header->bfReserved1);
    printf("  bfReserved2:     0x%x\n", file_header->bfReserved2);
    printf("  bfOffBits:       %d\n", file_header->bfOffBits);
    printf("BITMAPINFOHEADER:\n");
    printf("  biSize:          %d\n", info_header->biSize);
    printf("  biWidth:         %d\n", info_header->biWidth);
    printf("  biHeight:        %d\n", info_header->biHeight);
    printf("  biPlanes:        %d\n", info_header->biPlanes);
    printf("  biBitCount:      %d\n", info_header->biBitCount);
    printf("  biCompression:   %d\n", info_header->biCompression);
    printf("  biSizeImage:     %d\n", info_header->biSizeImage);
    printf("  biXPelsPerMeter: %d\n", info_header->biXPelsPerMeter);
    printf("  biYPelsPerMeter: %d\n", info_header->biYPelsPerMeter);
    printf("  biClrUsed:       %d\n", info_header->biClrUsed);
    printf("  biClrImportant:  %d\n", info_header->biClrImportant);
}

int print_color_percentage(int *arr, int len)
{
    for (int i = 0; i < 16; i++)
    {
        double percentage = (double)arr[i] / (len / 3) * 100;
        printf("  %d-%d: %.2lf\n", 16 * i, 16 * (i + 1) - 1, percentage);
    }
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("Invalid number of arguments\n");
        return 1;
    }
    FILE *bmp_file = fopen(argv[1], "rb");
    if (bmp_file == NULL)
    {
        printf("Error opening bmp file\n");
        return 1;
    }

    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;
    unsigned char *pixel_data;

    read_bmp(bmp_file, &file_header, &info_header, &pixel_data);
    // print_bmp(&file_header, &info_header);
    pixel_data = malloc(info_header.biSizeImage);

    if (pixel_data == NULL)
    {
        printf("Error allocating memory");
    }

    if (info_header.biCompression != 0 && info_header.biBitCount != 24)
    {
        printf("Histogram calculation is unsupported\n");
    }
    else
    {
        // info_header.biSizeImage = 30;

        // fread(pixel_data, info_header.biSizeImage, 1, bmp_file);

        int red[16] = {0};
        int green[16] = {0};
        int blue[16] = {0};
        int length = info_header.biSizeImage;
        int row_length = ((24 * info_header.biWidth + 31) / 32) * 4;
        int height = info_header.biHeight;

        // Move pointer to RGB pixel part
        fseek(bmp_file, file_header.bfOffBits, SEEK_SET);

        for (int row = 0; row < info_header.biHeight; row++)
        {
            // read row
            fread(pixel_data, row_length, 1, bmp_file);
            for (int i = 0; i <= row_length; i += 3)
            {
                int b = pixel_data[i];
                int g = pixel_data[i + 1];
                int r = pixel_data[i + 2];
                red[r / 16]++;
                green[g / 16]++;
                blue[b / 16]++;
                // printf("rgb: %u %u %u\n", r, g, b);
            }
        }
        printf("Blue:\n");
        print_color_percentage(blue, length);
        printf("Green:\n");
        print_color_percentage(green, length);
        printf("Red:\n");
        print_color_percentage(red, length);
    }

    fclose(bmp_file);
    free(pixel_data);

    return 0;
}