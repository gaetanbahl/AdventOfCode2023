#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void display_vec(vector<uint64_t> v) {
    for (int n : v) {
        cout << n << " ";
    }
    cout << endl;
}

uint64_t compute_distance(uint64_t time_pressed, uint64_t race_time) {
    uint64_t speed = time_pressed;
    return speed*(race_time - time_pressed);
}

int main() {

    string filename = "input copy.txt"; // input with spaces removed because I'm lazy
    // string filename = "example copy.txt";

    ifstream istrm(filename);

    if (!istrm.is_open()) {
        cout << "Failed to open " << filename << endl;
    } else {
        string s, word;

        vector<uint64_t> times;
        vector<uint64_t> distances;
        
        getline(istrm, s);
        stringstream strm(s);
        strm >> word;
        uint64_t n;
        while(strm >> n) {
            times.push_back(n);
        }

        getline(istrm, s);
        stringstream strm2(s);
        strm2 >> word;
        while(strm2 >> n) {
            distances.push_back(n);
        }


        uint number_beaten = 0;

        for (int i = 0; i < times.size(); i++) {
            for(int t = 0; t < times[i]; t++) {
                if (compute_distance(t, times[i]) > distances[i]) {
                    number_beaten++;
                }
            }
        }

        cout << number_beaten << endl;
    }

    return 0;
}