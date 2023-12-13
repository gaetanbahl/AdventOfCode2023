#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>

// const size_t N_WINNING = 5;
// const size_t N = 8;
// const size_t N_CARDS = 6;


const size_t N_WINNING = 10;
const size_t N = 25;
const size_t N_CARDS = 213;

int main() {

    std::string filename = "input.txt";
    // std::string filename = "example.txt";

    std::ifstream istrm(filename);

    if (!istrm.is_open()) {
        std::cout << "Failed to open " << filename << std::endl;
    } else {
        std::string s;
        int total = 0;

        int n;
        std::string word;
        std::vector<int> multipliers(N_CARDS, 1);
        int curr = 0;
        while(std::getline(istrm, s)) {
            std::stringstream strm(s);
            strm >> word >> word;

            int score = 0;
            std::set<int> winning_numbers;
            std::set<int> played_numbers;
            for(int i=0; i<N_WINNING; i++) {
                strm >> n;
                winning_numbers.insert(n);
            }
            strm >> word;
            for(int i=0; i<N; i++) {
                strm >> n;
                played_numbers.insert(n);
            }

            for (int num : played_numbers) {
                if (winning_numbers.count(num) > 0) {
                    score++;
                    multipliers[curr+score] += multipliers[curr];
                }
            }
            total += multipliers[curr];
            curr++;
        }
        std::cout << total << std::endl;
    }

    return 0;
}