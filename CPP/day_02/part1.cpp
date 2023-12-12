#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {

    std::string filename = "input.txt";

    std::ifstream istrm(filename);

    if (!istrm.is_open()) {
        std::cout << "Failed to open " << filename << std::endl;
    } else {
        std::string s;
        int total = 0;
        int max_blue = 14;
        int max_red = 12;
        int max_green = 13;

        int n;
        int id = 1;
        std::string word;
        while(std::getline(istrm, s)) {
            std::stringstream strm(s);
            bool impossible = false;
            strm >> word >> word;
            while(strm >> n >> word) {
                switch (word[0])
                {
                case 'r':
                    if (n > max_red) impossible = true; 
                    break;
                case 'b':
                    if (n > max_blue) impossible = true;
                    break;
                case 'g':
                    if (n > max_green) impossible = true;
                    break;
                default:
                    break;
                }
            }

            if (!impossible)
                total += id;
            id++;
        }
        std::cout << total << std::endl;
    }

    return 0;
}