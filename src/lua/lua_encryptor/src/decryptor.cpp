#include "stdio.h"
#include "stdlib.h"
#include "xxtea.h"

#define FILE_LEN 1024*1024*10
#define KEY "123456"

int main(int argc, char *argv[])
{
    FILE *file;
    char* inPath = argv[1];
    char* outPath = argv[2];
    unsigned char* fileData = (unsigned char*)malloc(FILE_LEN);

    file = fopen(inPath, "rb");
    size_t num = fread(fileData, 1, FILE_LEN, file);
    fclose(file);

    size_t dataLen = 0;

    unsigned char* data = (unsigned char*)xxtea_decrypt(fileData, num, KEY, &dataLen);

    file = fopen(outPath, "web+");
    fwrite(data, 1, dataLen, file);
    fclose(file);

    return 0;
}
