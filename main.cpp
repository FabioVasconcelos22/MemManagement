#include <iostream>
#include <memory>

int GetFileLength (FILE *in ) {
    int length = 0;

    while (fgetc(in) != EOF) {
        ++length;
    }
    return length;
}

void toUpper64bytes (FILE *in, FILE *out, int pos) {

    char* Buffer;

    for (int i=0; i<64; i++) {
        Buffer = &in[i];
    }
    return Buffer;
};

int main(int argc, char *argv[]) {

    FILE * inputFile;
    FILE * outputFile;

    inputFile = fopen ("../source.txt" , "r");
    outputFile = fopen ("../output.txt" , "w");

    if(inputFile == nullptr || outputFile == nullptr) {
        std::cerr << "Error opening the file" << std::endl;
        return 0;
    }

    for ( int i = 0; i <= GetFileLength (inputFile); i+=64) {
        toUpper64bytes(inputFile, outputFile, i);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
