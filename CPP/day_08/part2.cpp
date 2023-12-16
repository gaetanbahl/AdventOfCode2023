#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

bool check_end(vector<string> nodes) {
    bool end = true;
    for (string n : nodes) {
        if (!n.ends_with('Z')) {
            end = false;
            break;
        }
    }
    return end;
}


int main() {

    string filename = "input.txt";
    // string filename = "example3.txt";

    ifstream istrm(filename);

    if (!istrm.is_open()) {
        cout << "Failed to open " << filename << endl;

        return 1;
    }

    unordered_map<string, pair<string, string>> paths;
    string instructions;
    vector<string> starting_nodes;

    string s;
    getline(istrm, instructions);
    getline(istrm, s);

    string node, colon, left_child, right_child;

    while(istrm >> node >> colon >> left_child >> right_child) {
        left_child = left_child.substr(1, 3);
        right_child = right_child.substr(0, 3);

        if (node.ends_with('A')) {
            starting_nodes.push_back(node);
        }

        paths[node] = {left_child, right_child};
    }

    int i = 0;
    vector<string> curr = starting_nodes;

    while(!check_end(curr)) {
        switch (instructions[i%instructions.size()])
        {
        case 'L':
            for (int j = 0; j < curr.size(); j++) {  
                curr[j] = paths[curr[j]].first;
            }
            break;
        case 'R':
            for (int j = 0; j < curr.size(); j++) {  
                curr[j] = paths[curr[j]].second;
            }
        default:
            break;
        }
        i++;

        for (int j = 0 ; j < curr.size(); j++) {
            if (curr[j].ends_with('Z')) {
                cout << j << " " << curr[j] << " " << i << endl;
                break;
            }
        }
        if (i > 100000) break;
    }

    cout << i << endl;

    return 0;
}