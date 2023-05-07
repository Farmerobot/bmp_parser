#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

void read_bmp(FILE *bmp_file, BITMAPFILEHEADER *file_header, BITMAPINFOHEADER *info_header)
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
    printf("  bfType:          0x%x (%c%c)\n", file_header->bfType, (char)(file_header->bfType), (char)(file_header->bfType >> 8));
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

void write_bmp(FILE *output_file, BITMAPFILEHEADER *file_header, BITMAPINFOHEADER *info_header)
{
    fwrite(&file_header->bfType, sizeof(file_header->bfType), 1, output_file);
    fwrite(&file_header->bfSize, sizeof(file_header->bfSize), 1, output_file);
    fwrite(&file_header->bfReserved1, sizeof(file_header->bfReserved1), 1, output_file);
    fwrite(&file_header->bfReserved2, sizeof(file_header->bfReserved2), 1, output_file);
    fwrite(&file_header->bfOffBits, sizeof(file_header->bfOffBits), 1, output_file);
    fwrite(&info_header->biSize, sizeof(info_header->biSize), 1, output_file);
    fwrite(&info_header->biWidth, sizeof(info_header->biWidth), 1, output_file);
    fwrite(&info_header->biHeight, sizeof(info_header->biHeight), 1, output_file);
    fwrite(&info_header->biPlanes, sizeof(info_header->biPlanes), 1, output_file);
    fwrite(&info_header->biBitCount, sizeof(info_header->biBitCount), 1, output_file);
    fwrite(&info_header->biCompression, sizeof(info_header->biCompression), 1, output_file);
    fwrite(&info_header->biSizeImage, sizeof(info_header->biSizeImage), 1, output_file);
    fwrite(&info_header->biXPelsPerMeter, sizeof(info_header->biXPelsPerMeter), 1, output_file);
    fwrite(&info_header->biYPelsPerMeter, sizeof(info_header->biYPelsPerMeter), 1, output_file);
    fwrite(&info_header->biClrUsed, sizeof(info_header->biClrUsed), 1, output_file);
    fwrite(&info_header->biClrImportant, sizeof(info_header->biClrImportant), 1, output_file);

    // handle file padding
    int offset = file_header->bfOffBits - 54;
    char padding[offset];
    memset(padding, 0, offset);
    fwrite(padding, offset, 1, output_file);
}

void print_color_percentage(int *arr, int len)
{
    for (int i = 0; i < 16; i++)
    {
        double percentage = (double)arr[i] / (len / 3) * 100;
        printf("  %d-%d: %.2lf%\n", 16 * i, 16 * (i + 1) - 1, percentage);
    }
}

void print_all_color_percentages(int *blue, int *green, int *red, int length)
{
    printf("Blue:\n");
    print_color_percentage(blue, length);
    printf("Green:\n");
    print_color_percentage(green, length);
    printf("Red:\n");
    print_color_percentage(red, length);
}

int main(int argc, char **argv)
{
    char *output_file_name = NULL;
    char *text_to_encode = NULL;
    bool decode_secret = false;
    if (argc <= 1)
    {
        printf("Invalid number of arguments\n");
        return 1;
    }
    // 4.0, grayscale
    else if (argc == 3)
    {
        output_file_name = argv[2];
    }
    // 4.5, steganography
    else if (argc == 4)
    {
        output_file_name = argv[2];
        text_to_encode = argv[3];

        if (strlen(text_to_encode) > 255)
        {
            printf("Message to encode must be at most 255 characters long\n");
            return 1;
        }
        // Insert length as first char
        memmove(text_to_encode + 1, text_to_encode, strlen(text_to_encode) + 1);
        text_to_encode[0] = strlen(text_to_encode);
    }

    FILE *bmp_file = fopen(argv[1], "rb");
    FILE *output_file = NULL;

    if (bmp_file == NULL)
    {
        printf("Error opening bmp file\n");
        return 1;
    }

    // Ask to decode
    char choice;
    printf("Decode steganography? [Y/n] ");
    scanf("%c", &choice);
    if (choice == 'y' || choice == 'Y') {
        decode_secret = true;
    }
    decode_secret = true;

    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;
    unsigned char *pixel_data;
    unsigned char *output_pixel_data;

    read_bmp(bmp_file, &file_header, &info_header);

    // 3.0
    print_bmp(&file_header, &info_header);

    if (info_header.biCompression != 0 && info_header.biBitCount != 24)
    {
        printf("Histogram calculation is unsupported\n");
    }
    // 3.5
    else
    {
        int red[16] = {0};
        int green[16] = {0};
        int blue[16] = {0};
        int length = info_header.biSizeImage;
        int row_length = ((24 * info_header.biWidth + 31) / 32) * 4;
        int height = info_header.biHeight;

        // 4.0
        if (output_file_name != NULL)
        {
            output_file = fopen(output_file_name, "wb");
            if (output_file == NULL)
            {
                printf("Error creating output file:'%s'\n", output_file_name);
                return 1;
            }

            write_bmp(output_file, &file_header, &info_header);
            output_pixel_data = malloc(row_length);
        }
        pixel_data = malloc(row_length);
        if (pixel_data == NULL)
        {
            printf("Error allocating memory\n");
        }

        // Move pointer to RGB pixel part
        fseek(bmp_file, file_header.bfOffBits, SEEK_SET);

        char decoded_string[255];
        memset(decoded_string, 0, 255);
        decoded_string[254] = '\0';

        int decoded_string_length = 0;

        char binary_str[17];
        binary_str[16] = '\0'; // null terminator for the string
        // binary encoding bit iterator
        int binary_counter = 0;
        for (int row = 0; row < info_header.biHeight; row++)
        {
            // read row
            fread(pixel_data, row_length, 1, bmp_file);
            for (int i = 0; i < row_length; i += 3)
            {
                int b = pixel_data[i];
                int g = pixel_data[i + 1];
                int r = pixel_data[i + 2];
                red[r / 16]++;
                green[g / 16]++;
                blue[b / 16]++;

                // Decode
                if (decode_secret)
                {
                    // Iterate over rgb
                    unsigned char *ptr = pixel_data + i;
                    for (int byte = 0; byte < 3; byte++)
                    {
                        int rgb_byte = binary_counter + byte;
                        if (rgb_byte > 8 * decoded_string_length && rgb_byte > 8)
                        {
                            break;
                        }
                        int encoded_byte = (int)*(ptr + byte);
                        // read text length from first byte
                        if (rgb_byte < 8)
                        {
                            decoded_string_length <<= 1;
                            decoded_string_length |= (encoded_byte & 0x01);
                            continue;
                        }
                        // printf("rgb: %d %d %d, ", pixel_data[i], pixel_data[i + 1], pixel_data[i + 2]);
                        // printf("ptr: %d, %d, %d, %d\n", encoded_byte, b, g, r);
                        decoded_string[(rgb_byte) / 8] <<= 1;
                        decoded_string[(rgb_byte) / 8] |= (encoded_byte & 0x01);
                        // binary_str[rgb_byte] = (encoded_byte & 0x01) == 0 ? '0' : '1';
                    }
                }
                // decoded_string[binary_counter / 8] <<= 1;
                // decoded_string[binary_counter / 8] |= (b & 0x01);
                // binary_str[binary_counter] = (b & 0x01) == 0 ? '0' : '1';

                // decoded_string[(binary_counter + 1) / 8] <<= 1;
                // decoded_string[(binary_counter + 1) / 8] |= (g & 0x01);
                // binary_str[binary_counter + 1] = (g & 0x01) == 0 ? '0' : '1';

                // decoded_string[(binary_counter + 2) / 8] <<= 1;
                // decoded_string[(binary_counter + 2) / 8] |= (r & 0x01);
                // binary_str[binary_counter + 2] = (r & 0x01) == 0 ? '0' : '1';

                // 4.0
                if (output_file_name != NULL)
                {
                    int grayscale = (r + g + b) / 3;
                    output_pixel_data[i] = grayscale;
                    output_pixel_data[i + 1] = grayscale;
                    output_pixel_data[i + 2] = grayscale;
                    // 4.5
                    // Encode binary data from string
                    if (text_to_encode != NULL)
                    {
                        for (int bit = 0; bit < 3; bit++)
                        {
                            int rgb_bit = binary_counter + bit;
                            // reached end of string
                            if (rgb_bit > 8 * strlen(text_to_encode))
                            {
                                break;
                            }
                            char char_to_encode = text_to_encode[rgb_bit / 8];
                            unsigned bit_to_encode = ((char_to_encode >> (7 - (rgb_bit % 8))) & 0x01);
                            // set bit to 0 with AND
                            if (bit_to_encode == 0)
                            {
                                output_pixel_data[i + bit] &= 0b11111110;
                            }
                            // set bit to 1 with OR
                            else
                            {
                                output_pixel_data[i + bit] |= 0b00000001;
                            }
                        }
                    }
                }
                binary_counter += 3;
                // printf("%d\n", binary_counter);
                // printf("rgb: %u %u %u\n", r, g, b);

                // if (binary_counter >= 16)
                // {
                //     return 0;
                // }
            }
            // 4.0
            if (output_file_name != NULL)
            {
                fwrite(output_pixel_data, row_length, 1, output_file);
            }
        }
        // printf("bin: %s\n", binary_str);
        if (decode_secret) {
            printf("Decoded string: '%s', len: %d\n", decoded_string + 1, decoded_string_length);
        }
        // 3.5
        // print_all_color_percentages(blue, green, red, length);
    }

    if (output_file_name != NULL)
    {
        fclose(output_file);
        free(output_pixel_data);
    }
    fclose(bmp_file);
    free(pixel_data);

    return 0;
}