#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> compute_differences(vector<int> &sequence) {
    vector<int> ret;
    ret.reserve(sequence.size()-1);
    for (uint i = 0; i < sequence.size()-1; i++) {
        ret.push_back(sequence[i+1] - sequence[i]);
    }
    return ret;
}

bool all_zeroes(vector<int> &seq) {
    for (int n : seq) {
        if (n != 0) 
            return false;
    }
    return true;
}

void display_vec(vector<int> &v) {
    for (int n : v) {
        cout << n << " ";
    }
    cout << endl;
}


int main() {

    string filename = "input.txt";
    // string filename = "example.txt";

    ifstream istrm(filename);

    if (!istrm.is_open()) {
        cout << "Failed to open " << filename << endl;
        return 1;
    }

    string s;

    int total = 0;

    while(getline(istrm, s)) {
        stringstream strstrm(s);

        vector<int> sequence;
        int n;
        while(strstrm >> n) {
            sequence.push_back(n);
        }


        vector<int> curr = sequence;
        vector<vector<int>> history;
        while(!all_zeroes(curr)) {
            history.push_back(curr);
            curr = compute_differences(curr);
        }
        history.push_back(curr);

        history[history.size()-1].push_back(0);

        for(int i = history.size() - 2; i >= 0; i--) {
            total += history[i].back();
        }

    }

    cout << total << endl;

    return 0;
}