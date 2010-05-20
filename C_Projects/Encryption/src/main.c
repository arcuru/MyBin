#include <stdio.h>
#include <stdlib.h>

void encode(char plain[], char target[], char key[], int keylength,
            int settings)
{
    FILE* original = fopen(plain, "r");
    FILE* encoded = fopen(target, "w");
    if (!original || !encoded) {
        fprintf(stderr, "Could not open file.");
        fclose(original);
        fclose(encoded);
        return;
    }
    char writebuffer[BUFSIZ];
    setbuf(encoded, writebuffer);
    fseek(original, 0, SEEK_END);
    long filelength = ftell(original);
    fseek(original, 0, SEEK_SET);
    char* readbuffer = (char*) malloc(sizeof (char) * filelength);
    if (!readbuffer) {
        fprintf(stderr, "Not enough memory");
        fclose(original);
        fclose(encoded);
        return;
    }
    fread(readbuffer, 1, filelength, original);
    fclose(original);
    int readindex = 0, point = 0, out = 0;
    char c = readbuffer[readindex++];
    char *printstr = NULL, *delimiter = NULL;
    if (settings == 1) {
        printstr = "%d";
        delimiter = ",";
    } else {
        printstr = "%02d";
        delimiter = "";
    }
    while (readindex <= filelength) {
        out = (int) c ^ key[(point++) % keylength];
        fprintf(encoded, printstr, out);
        fprintf(stdout, printstr, out);
        c = readbuffer[readindex++];
        if (readindex <= filelength) {
            fprintf(encoded, "%s", delimiter);
            fprintf(stdout, "%s", delimiter);
        }
    }
    fclose(encoded);
    free(readbuffer);
    return;
}

void decode(char encoded[], char target[], char key[], int keylength,
            int settings)
{
    FILE* original = fopen(encoded, "r");
    FILE* plain = fopen(target, "w");
    if (!original || !plain) {
        fprintf(stderr, "Could not open file.");
        fclose(original);
        fclose(plain);
        return;
    }
    char writebuffer[BUFSIZ];
    setbuf(plain, writebuffer);
    int point = 0, c = 0, out = 0;
    while (fscanf(original, "%2d", &c)) {
        out = c ^ key[(point++) % keylength];
        fprintf(plain, "%c", out);
        fprintf(stdout, "%c", out);
        if (fgetc(original) == EOF)
            break;
        if (settings == 0)
            fseek(original, -1, SEEK_CUR);
    }
    fclose(original);
    fclose(plain);
    return;
}

int main()
{
    decode("data/code.txt", "data/log.txt", "patrick", 7, 1);
    printf("\n");
//    encode("data/log.txt", "data/test.txt", "patrick", 7, 0);
//    printf("\n");
//    decode("data/test.txt", "data/test2.txt", "patrick", 7, 0);
//    printf("\n");
//    encode("data/log.txt", "data/test.txt", "patrick", 7, 1);
    return 0;
}
