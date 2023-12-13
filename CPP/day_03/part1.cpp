#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


const size_t N = 140;

int ctoi(char c) {
    return c - '0';
}

bool c_is_num(char c) {
    return c >= '0' && c <= '9';
}

bool check(char mat[N][N], size_t i, size_t j) {
    return (mat[i][j] < '0' || mat[i][j] > '9') && mat[i][j] != '.';
}

bool checkfirst(char mat[N][N], size_t i, size_t j) {

    bool ret = false;

    if (j > 0) {
        ret |= check(mat, i, j-1);
        if (i > 0) ret |= check(mat, i-1, j-1);
        if (i < N-1) ret |= check(mat, i+1, j-1);
    }
    if (i > 0) ret |= check(mat, i-1, j);
    if (i < N-1) ret |= check(mat, i+1, j);

    return ret;
}

bool checklast(char mat[N][N], size_t i, size_t j) {

    bool ret = false;
    
    if (j < N-1) {
        ret |= check(mat, i, j+1);
        if (i > 0) ret |= check(mat, i-1, j+1);
        if (i < N-1) ret |= check(mat, i+1, j+1);
    }
    if (i > 0) ret |= check(mat, i-1, j);
    if (i < N-1) ret |= check(mat, i+1, j);

    return ret;
}

bool checkmid(char mat[N][N], size_t i, size_t j) {

    bool ret = false;

    if (i > 0) ret |= check(mat, i-1, j);
    if (i < N-1) ret |= check(mat, i+1, j);

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
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                istrm >> mat[i][j];
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

                    bool is_part = checkfirst(mat, i, j);
                    if (j < N-2 && c_is_num(mat[i][j+1]) && c_is_num(mat[i][j+2])) {
                        std::cout << "three digit number" << std::endl;
                        std::cout << mat[i][j] << mat[i][j+1] << mat[i][j+2] << std::endl;
                        is_part |= checkmid(mat, i, j+1);
                        is_part |= checklast(mat, i, j+2);
                        if (is_part) 
                            sum += ctoi(mat[i][j]) * 100 + ctoi(mat[i][j+1]) * 10 + ctoi(mat[i][j+2]);
                        j += 2;
                    } else if (j < N-1 && c_is_num(mat[i][j+1])) {
                        std::cout << "two digit number" << std::endl;
                        std::cout << mat[i][j] << mat[i][j+1] << std::endl;
                        is_part |= checklast(mat, i, j+1);
                        if (is_part) 
                            sum += ctoi(mat[i][j]) * 10 + ctoi(mat[i][j+1]);
                        j++;
                    } else {
                        std::cout << "one digit number" << std::endl;
                        std::cout << mat[i][j] << std::endl;
                        is_part |= checklast(mat, i, j);
                        if (is_part) 
                            sum += ctoi(mat[i][j]);
                    }
                    std::cout << is_part << std::endl;  
                }
            }
        }

        std::cout << sum << std::endl;
    }

    return 0;
}