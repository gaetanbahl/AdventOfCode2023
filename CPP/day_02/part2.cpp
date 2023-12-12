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

        int n;
        int id = 1;
        std::string word;
        while(std::getline(istrm, s)) {
            int max_blue = 0;
            int max_red = 0;
            int max_green = 0;
            std::stringstream strm(s);
            strm >> word >> word;
            while(strm >> n >> word) {
                switch (word[0])
                {
                case 'r':
                    if (n > max_red) max_red = n; 
                    break;
                case 'b':
                    if (n > max_blue) max_blue = n;
                    break;
                case 'g':
                    if (n > max_green) max_green = n;
                    break;
                default:
                    break;
                }
            }

            total += max_blue * max_green * max_red;
            id++;
        }
        std::cout << total << std::endl;
    }

    return 0;
}