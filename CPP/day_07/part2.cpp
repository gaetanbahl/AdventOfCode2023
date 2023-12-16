#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

typedef pair<char, uint> card;

unordered_map<char, uint> card_to_value = {{'J',1},
                                            {'2',2}, 
                                            {'3',3},
                                            {'4',4},
                                            {'5',5},
                                            {'6',6},
                                            {'7',7},
                                            {'8',8},
                                            {'9',9},
                                            {'T',10},
                                            {'Q',11},
                                            {'K',12},
                                            {'A',13}};

void display_vec(vector<int> v) {
    for (int n : v) {
        cout << n << " ";
    }
    cout << endl;
}

struct hand {
    vector<card> cards;
    uint bid;
    vector<uint> card_values;
    uint type;
    uint jokers;

    hand(string cards_str, uint bid);

    bool is_five_kind();
    bool is_four_kind();
    bool is_full_house();
    bool is_three_kind();
    bool is_two_pair();
    bool is_one_pair();
    bool is_high_card();

};

hand::hand(string cards_str, uint bid) {
    this->jokers = 0;
    this->card_values.reserve(5);
    for (char c : cards_str) {
        bool found = false;

        this->card_values.push_back(card_to_value[c]);

        if (c == 'J') {
            this->jokers++;
            continue;
        }

        for (int i=0; i<cards.size(); i++) {
            card curr = this->cards[i];
            if (curr.first == c) {
                this->cards[i] = {c, curr.second+1};
                found=true;
            }
        }
        if (!found) {
            this->cards.push_back({c, 1});
        }
    }
    sort(this->cards.begin(), this->cards.end(), [](card a, card b)
                                {
                                    return a.second > b.second;
                                });
    this->bid = bid;

    if (this->cards.size() > 0) {
        this->cards[0] = {this->cards[0].first, this->cards[0].second + this->jokers};
    } else {
        this->cards.push_back({'J', this->jokers});
    }

    if(this->is_five_kind()) {
        this->type = 7;
    } else if(this->is_four_kind()) {
        this->type = 6;
    } else if(this->is_full_house()) {
        this->type = 5;
    } else if(this->is_three_kind()) {
        this->type = 4;
    } else if(this->is_two_pair()) {
        this->type = 3;
    } else if(this->is_one_pair()) {
        this->type = 2;
    } else if(this->is_high_card()) {
        this->type = 1;
    }
}

bool hand::is_five_kind() {
    return this->cards.size() == 1;
}

bool hand::is_four_kind() {
    if (this->cards.size() != 2)
        return false;

    if (this->cards[0].second == 4)
        return true;

    return false;
}

bool hand::is_full_house() {
    if (this->cards.size() != 2)
        return false;

    if (this->cards[0].second == 3 && this->cards[1].second == 2)
        return true;

    return false;
}

bool hand::is_three_kind() {
    if (this->cards.size() != 3)
        return false;

    if (this->cards[0].second == 3 && this->cards[1].second == 1)
        return true;

    return false;
}

bool hand::is_two_pair() {
    if (this->cards.size() != 3)
        return false;

    if (this->cards[0].second == 2 && this->cards[1].second == 2)
        return true;

    return false;
}

bool hand::is_one_pair() {
    if (this->cards.size() != 4)
        return false;

    if (this->cards[0].second == 2)
        return true;

    return false;
}

bool hand::is_high_card() {
    return this->cards.size() == 5;
}

bool operator<(hand h1, hand h2) {
    if (h1.type != h2.type) {
        return h1.type <= h2.type;
    } else {
        for(int i=0; i<h1.card_values.size(); i++) {
            if (h1.card_values[i] < h2.card_values[i]) {
                return true;
            } else if(h1.card_values[i] > h2.card_values[i]) {
                return false;
            }
        }
    }
    return false;
}

int main() {

    string filename = "input.txt";
    // string filename = "example.txt";

    ifstream istrm(filename);

    if (!istrm.is_open()) {
        cout << "Failed to open " << filename << endl;
    } else {
        string word;
        uint bid;

        vector<hand> hands;

        while(istrm >> word >> bid) {
            struct hand h(word, bid);
            hands.push_back(h);
        }

        sort(hands.begin(), hands.end(), [](hand h1, hand h2){return h1 < h2;});

        uint winnings = 0;
        for (int i = 0; i < hands.size(); i++) {
            winnings += (i+1) * hands[i].bid;
        }

        cout << winnings << endl;

    }

    return 0;
}