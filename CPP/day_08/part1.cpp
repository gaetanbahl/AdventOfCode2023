#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;


int main() {

    string filename = "input.txt";
    // string filename = "example2.txt";

    ifstream istrm(filename);

    if (!istrm.is_open()) {
        cout << "Failed to open " << filename << endl;

        return 1;
    }

    unordered_map<string, pair<string, string>> paths;
    string instructions;

    string s;
    getline(istrm, instructions);
    getline(istrm, s);

    string node, colon, left_child, right_child;

    while(istrm >> node >> colon >> left_child >> right_child) {
        left_child = left_child.substr(1, 3);
        right_child = right_child.substr(0, 3);

        paths[node] = {left_child, right_child};
    }

    int i = 0;
    string curr = "AAA";

    while(curr != "ZZZ") {
        switch (instructions[i%instructions.size()])
        {
        case 'L':
            curr = paths[curr].first;
            break;
        case 'R':
            curr = paths[curr].second;
        default:
            break;
        }

        i++;
    }

    cout << i << endl;

    return 0;
}