#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void display_vec(vector<int> v) {
    for (int n : v) {
        cout << n << " ";
    }
    cout << endl;
}

uint compute_distance(uint time_pressed, uint race_time) {
    uint speed = time_pressed;
    return speed*(race_time - time_pressed);
}

int main() {

    string filename = "input.txt";
    // string filename = "example.txt";

    ifstream istrm(filename);

    if (!istrm.is_open()) {
        cout << "Failed to open " << filename << endl;
    } else {
        string s, word;

        uint result = 1;

        vector<uint> times;
        vector<uint> distances;
        getline(istrm, s);
        stringstream strm(s);
        strm >> word;
        uint n;
        while(strm >> n) {
            times.push_back(n);
        }

        getline(istrm, s);
        stringstream strm2(s);
        strm2 >> word;
        while(strm2 >> n) {
            distances.push_back(n);
        }

        for (int i = 0; i < times.size(); i++) {
            int number_beaten = 0;
            for(int t = 0; t < times[i]; t++) {
                if (compute_distance(t, times[i]) > distances[i]) {
                    number_beaten++;
                }
            }
            result *= number_beaten;
        }

        cout << result << endl;
    }

    return 0;
}