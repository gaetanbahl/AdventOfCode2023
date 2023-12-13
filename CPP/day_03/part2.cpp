#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <unordered_map>

const size_t N = 140;

int ctoi(char c) {
    return c - '0';
}

bool c_is_num(char c) {
    return c >= '0' && c <= '9';
}

int check(char mat[N][N], size_t i, size_t j) {
    if (mat[i][j] == '*') {
        return N*i + j;
    } else {
        return -1;
    }
}

int checkfirst(char mat[N][N], size_t i, size_t j) {

    int ret = -1;

    if (j > 0) {
        ret = check(mat, i, j-1);
        if (ret !=  -1) return ret; // sue me lol
        if (i > 0) ret = check(mat, i-1, j-1);
        if (ret !=  -1) return ret;
        if (i < N-1) ret = check(mat, i+1, j-1);
        if (ret !=  -1) return ret;
    }
    if (i > 0) ret = check(mat, i-1, j);
    if (ret !=  -1) return ret;
    if (i < N-1) ret = check(mat, i+1, j);
    if (ret !=  -1) return ret;

    return ret;
}

int checklast(char mat[N][N], size_t i, size_t j) {

    int ret = -1;
    
    if (j < N-1) {
        ret = check(mat, i, j+1);
        if (ret != -1) return ret;
        if (i > 0) ret = check(mat, i-1, j+1);
        if (ret != -1) return ret;
        if (i < N-1) ret = check(mat, i+1, j+1);
        if (ret != -1) return ret;
    }
    if (i > 0) ret = check(mat, i-1, j);
    if (ret != -1) return ret;
    if (i < N-1) ret = check(mat, i+1, j);
    if (ret != -1) return ret;

    return ret;
}

int checkmid(char mat[N][N], size_t i, size_t j) {

    int ret = -1;

    if (i > 0) ret = check(mat, i-1, j);
    if (ret != -1) return ret;
    if (i < N-1) ret = check(mat, i+1, j);
    if (ret != -1) return ret;

    return ret;
}

int main() {

    std::string filename = "input.txt";

    std::ifstream istrm(filename);

    if (!istrm.is_open()) {
        std::cout << "Failed to open " << filename << std::endl;
    } else {

        char mat[N][N];
        char c;
        int sum = 0;
        int count = 0;
        std::unordered_map<int, std::vector<int>> map;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                istrm >> mat[i][j];
                if (mat[i][j] == '*') {
                    count++;
                    std::vector<int> v;
                    map[N*i+j] = v;
                }
            }
        }

        // for (int i = 0; i < N; i++) {
        //     for (int j = 0; j < N; j++) {
        //         std::cout << mat[i][j];
        //     }
        //     std::cout << std::endl;
        // }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (c_is_num(mat[i][j])) {
                    int number;
                    int coord = checkfirst(mat, i, j);
                    if (j < N-2 && c_is_num(mat[i][j+1]) && c_is_num(mat[i][j+2])) {
                        // std::cout << "three digit number" << std::endl;
                        // std::cout << mat[i][j] << mat[i][j+1] << mat[i][j+2] << std::endl;
                        if (coord == -1) coord = checkmid(mat, i, j+1);
                        if (coord == -1) coord = checklast(mat, i, j+2);
                        number = ctoi(mat[i][j]) * 100 + ctoi(mat[i][j+1]) * 10 + ctoi(mat[i][j+2]);
                        // std::cout << coord << std::endl;
                        j += 2;
                    } else if (j < N-1 && c_is_num(mat[i][j+1])) {
                        // std::cout << "two digit number" << std::endl;
                        // std::cout << mat[i][j] << mat[i][j+1] << std::endl;
                        if (coord == -1) coord = checklast(mat, i, j+1);
                        number = ctoi(mat[i][j]) * 10 + ctoi(mat[i][j+1]);
                        // std::cout << coord << std::endl;
                        j++;
                    } else {
                        // std::cout << "one digit number" << std::endl;
                        // std::cout << mat[i][j] << std::endl;
                        if (coord == -1) coord = checklast(mat, i, j);
                        number = ctoi(mat[i][j]);
                        // std::cout << coord << std::endl;
                    }
                    if (coord != -1) {
                        map[coord].push_back(number);
                    }  
                }
            }
        }

        for (auto const& [key, value] : map) {
            // std::cout << key / N << " " << key % N << " ";
            // for (auto p : value)
            //     std::cout << p << ' '; 
            // std::cout << std::endl;
            // std::cout << std::endl;
            if (value.size() == 2)
                sum += value[0] * value[1];
        }

        std::cout << sum << std::endl;
        // std::cout << count << std::endl;
        // std::cout << map.size() << std::endl;

    }

    return 0;
}