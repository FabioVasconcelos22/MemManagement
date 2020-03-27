#include <iostream>
#include <fstream>


int GetFileLength ( std::ifstream& in ) {

    int length;

    in.seekg(0,in.end);
    length = in.tellg();
    in.seekg(0, in.beg);

    return length;
}

std::string toUpper64bytes(std::ifstream& in, int pos) {
    char buffer[64];

    in.seekg(pos);
    in.read(buffer,64);

    for(int i = 0; i < 64; ++i) {
        buffer[i] = toupper(buffer[i]);
    }

    return buffer;
}

int main() {
    std::ifstream input;
    std::ofstream output;
    input.open("../source.txt");
    output.open("../output.txt");

    if( !( input.is_open() && output.is_open() ) ) {
        std::cout << "File opens with errors or file does not exist" << std::endl;
    }

    for (int i = 0; i <= GetFileLength(input) ; i+=64 ) {
        output << toUpper64bytes(input, i);
    }

    input.close();
    output.close();

    return 0;
}
