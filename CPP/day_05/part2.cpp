#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>

using namespace std;

typedef pair<uint64_t, uint64_t> seed;
typedef tuple<uint64_t, uint64_t, uint64_t, uint64_t> mapping;

void display_vec(vector<int64_t> v) {
    for (int64_t n : v) {
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

vector<seed> map_single(vector<seed> source, vector<mapping> almanac) {
    vector<seed> sources = source;
    vector<seed> dests;
    while(sources.size() > 0) {
        // cout << sources.size() << endl;
        seed s = sources.back();
        sources.pop_back();
        for(auto m : almanac) {
            uint64_t shift = get<2>(m) - get<0>(m);
            if (get<0>(m) <= s.first && get<1>(m) >= s.second) {
                // entire source range contained in almanac line
                dests.push_back({s.first + shift, s.second + shift});
                s = {0, 0};
                break;
            } else if (get<0>(m) <= s.first && get<1>(m) >= s.first && get<1>(m) < s.second) {
                // start included in range but end is not
                dests.push_back({s.first + shift, get<3>(m)});
                s = {get<1>(m)+1, s.second};
            } else if (get<0>(m) > s.first && get<0>(m) <= s.second && get<1>(m) >= s.second) {
                // end included in range but start is not
                dests.push_back({get<2>(m), s.second + shift});
                s = {s.first, get<0>(m)-1};
            } else if (get<0>(m) > s.first && get<1>(m) < s.second ) {
                // start and end of almanac line in source range
                dests.push_back({get<2>(m), get<3>(m)});
                s = {s.first, get<0>(m)-1};
                // seed news = {get<1>(m), s.second};
                sources.push_back({get<1>(m)+1, s.second});
            }
        }
        if (s.first != s.second )
            dests.push_back(s);
    }

    return dests;
}

uint64_t map_all(seed source, vector<vector<mapping>> mappings) {
    vector<seed> ret = {source};
    for (auto a : mappings) {
        ret = map_single(ret, a);
    }
    uint64_t min = UINT64_MAX;
    for (auto s : ret) min = s.first < min ? s.first : min;
    return min;
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

        vector<seed> seeds;
        getline(istrm, s);
        stringstream strm(s);
        strm >> word;
        uint64_t start, range;
        while(strm >> start >> range) {
            seed sd = {start, start+range-1};
            seeds.push_back(sd);
        }

        getline(istrm, s);
        getline(istrm, s);

        // display_vec(seeds);
        // cout << endl;

        vector<vector<mapping>> mappings(7);

        uint64_t source, dest;
        int64_t curr = 0;
        while(getline(istrm, s)) {
            stringstream strm(s);
            if (s.length() == 0) {
                curr++;
                if (curr > 6) break;
                getline(istrm, s);
                continue;
            }
            strm >> dest >> source >> range;
            mapping m(source, source + range - 1, dest, dest + range - 1);

            mappings[curr].push_back(m);
        }

        vector<uint64_t> results;
        for (seed s : seeds) {
            results.push_back(map_all(s, mappings));
        }

        cout << *min_element(results.begin(), results.end()) << endl;
    }

    return 0;
}