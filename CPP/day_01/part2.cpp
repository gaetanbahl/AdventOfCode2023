#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::string filename = "input.txt";

    std::ifstream istrm(filename);

    std::string digits[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", 
                            "zero", "one", "two", "three", "four", "five",
                            "six", "seven", "eight", "nine"};

    std::string s;
    int total = 0;
    if (!istrm.is_open()) {
        std::cout << "Failed to open " << filename << std::endl;
    } else {
        while(istrm >> s) {
            std::vector<int> posdigits(20, INT_MAX);
            std::vector<int> posdigitslast(20, INT_MIN);

            for (int i = 0; i < 20; i++) {
                std::size_t found = s.find(digits[i]);
                if (found != std::string::npos) {
                    posdigits[i] = found;
                }
                found = s.rfind(digits[i]);
                if (found != std::string::npos) {
                    posdigitslast[i] = found;
                }
            }
            for (auto & n : posdigits ) {
                std::cout << n << " ";
            }
            std::cout << std::endl;

            int min = std::distance(std::begin(posdigits), std::min_element(std::begin(posdigits), std::end(posdigits)));
            if (min > 9) min -= 10;

            int max = std::distance(std::begin(posdigitslast), std::max_element(std::begin(posdigitslast), std::end(posdigitslast)));
            if (max > 9) max -= 10;

            std::cout << min << max << std::endl;

            total += min * 10 + max;
        }
    }

    std::cout << total << std::endl;

    return 0;
}