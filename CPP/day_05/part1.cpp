#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>

using namespace std;

typedef tuple<uint, uint, uint, uint> mapping;

void display_vec(vector<int> v) {
    for (int n : v) {
        cout << n << " ";
    }
    cout << endl;
}

void display_vec_tuples(vector<mapping> v) {
    for (mapping n : v) {
        cout << get<0>(n) << " " << get<1>(n) << " " << get<2>(n) << " " << get<3>(n) << endl;
    }
    cout << endl;
}

uint map_single(uint source, vector<mapping> almanac) {
    for(auto m : almanac) {
        if (source >= get<0>(m) && source < get<1>(m)) {
            // cout << "source " << source << " maps to " << get<2>(m) + (source - get<0>(m)) << " with " << get<0>(m) << " " << get<1>(m) << " " << get<2>(m) << endl;
            return get<2>(m) + (source - get<0>(m));
        }
    }
    return source;
}

uint map_all(uint source, vector<vector<mapping>> mappings) {
    uint ret = source;
    // cout << "chain: " << ret << " ";
    for (auto a : mappings) {
        ret = map_single(ret, a);
        // cout << ret << " ";
    }
    // cout << endl;
    return ret;
}

int main() {

    string filename = "input.txt";
    // string filename = "example.txt";

    ifstream istrm(filename);

    if (!istrm.is_open()) {
        cout << "Failed to open " << filename << endl;
    } else {
        string s;

        string word;

        vector<uint> seeds;
        getline(istrm, s);
        stringstream strm(s);
        strm >> word;
        uint n;
        while(strm >> n) {
            seeds.push_back(n);
        }

        getline(istrm, s);
        getline(istrm, s);

        // display_vec(seeds);
        // cout << endl;

        vector<vector<mapping>> mappings(7);

        uint source, dest, range;
        int curr = 0;
        while(getline(istrm, s)) {
            stringstream strm(s);
            if (s.length() == 0) {
                curr++;
                if (curr > 6) break;
                getline(istrm, s);
                continue;
            }
            strm >> dest >> source >> range;
            mapping m(source, source + range, dest, dest + range);

            mappings[curr].push_back(m);
        }

        // display_vec_tuples(mappings[1]);

        vector<uint> results;
        for (uint s : seeds) {
            results.push_back(map_all(s, mappings));
        }

        cout << *min_element(results.begin(), results.end()) << endl;
    }

    return 0;
}