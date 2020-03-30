#include <iostream>
#include <memory>

int GetFileSize (FILE *in ) {
    int length = 0;

    while (fgetc(in) != EOF) {
        length++;
    }
    return length;
}

int main(int argc, char *argv[]) {

    FILE * inputFile;
    FILE * outputFile;

    char buffer[64];

    inputFile = fopen ("../source.txt" , "r");
    outputFile = fopen ("../output.txt" , "w");

    if (inputFile == nullptr || outputFile == nullptr) {
        std::cerr << "Error opening files" << std::endl;
        return 0;
    }

    if (fgetc(inputFile) == EOF) {
        std::cerr << "Input file is empty" << std::endl;
        return 0;
    }

    int size = GetFileSize(inputFile);

    //return stream to the beggining
    fseek(inputFile, 0, SEEK_SET);

    while (fgetc(inputFile) != EOF) {

        //come beck 1 position because of While verification
        fseek(inputFile, -1, SEEK_CUR);

        fgets(buffer, 64, inputFile);

        for(int i=0 ; i< 64 ; ++i) {
            buffer[i] = toupper(buffer[i]);
            putc(buffer[i], outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
