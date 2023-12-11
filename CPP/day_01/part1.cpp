#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::string filename = "input.txt";

    std::ifstream istrm(filename);

    std::string s;
    int total = 0;
    if (!istrm.is_open()) {
        std::cout << "Failed to open " << filename << std::endl;
    } else {
        while(istrm >> s) {
            int first = -1;
            int last;

            for (int i = 0; i < s.length(); i++) {
                // std::cout << s[i] << std::endl;
                if (s[i] >= 48 && s[i] <= 57) {
                    if (first == -1) first = s[i] - 48;
                    last = s[i] - 48;
                }
            }
            total += first * 10 + last;
        }
    }

    std::cout << total << std::endl;

    return 0;
}