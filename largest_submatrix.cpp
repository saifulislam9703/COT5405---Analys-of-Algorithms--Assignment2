#include <bits/stdc++.h>
using namespace std;
#include <chrono>
#include "helper.h"

struct Result {
    int maxSize;  
    int bottomRightRow;
    int bottomRightCol;
};

void dp_update(
    const vector<vector<uint8_t>>& mat,
    vector<vector<uint8_t>>& DP,
    int& maxSize,
    int& max_i,
    int& max_j) 
    {
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[0].size(); ++j) {
                if (mat[i][j] == 0)
                {
                    if (i==0 || j==0)
                    {
                        DP[i][j] = 1; // first row/col populate
                    } 

                    else 
                    {
                        DP[i][j] = min({DP[i-1][j], DP[i][j-1], DP[i-1][j-1]}) + 1;
                    }

                    if (DP[i][j] > maxSize) 
                    {
                        maxSize = DP[i][j];
                        max_i = i;
                        max_j = j;
                    }
                }
                //ELSE ALREADY SET 0 INITIALLY
            }
        }
    }

// DP 
Result largest_square(const vector<vector<uint8_t>>& mat) {
    vector<vector<uint8_t>> DP(mat.size(), vector<uint8_t>(mat[0].size(), 0));
    
    int maxSize = 0;
    int max_i = -1, max_j = -1;

    dp_update(mat, DP, maxSize, max_i, max_j);

    return {maxSize, max_i, max_j};
}

// Print matrix
void print_matrix(const vector<vector<uint8_t>>& mat, const Result& result) {
    int size = result.maxSize;
    cout << "Largest zero square" << "\n";
    cout << "Size: " << size << " x " << size << "\n";
    cout << "Sub-matrix:\n";
    cout << "starting at (" << result.bottomRightRow - size + 1 << "," << result.bottomRightCol - size + 1 << ")\n";
    cout << "ending at (" << result.bottomRightRow << "," << result.bottomRightCol << ")\n";
    for (int i = result.bottomRightRow - size + 1; i <= result.bottomRightRow; ++i) 
    {
        for (int j = result.bottomRightCol - size + 1; j <= result.bottomRightCol; ++j) 
        {
            cout << int(mat[i][j]) << " ";
        }

        cout << "\n";
    }
}

// Synthetic experiment
void run_exp() {
    vector<pair<int,int>> sizes =
    {
        {10,10}, 
        {10,100}, 
        {10,1000}, 
        {100,1000}, 
        {1000,1000}
    };
    
    mt19937 rng(random_device{}());

    for (auto [m,n] : sizes) {
        cout << "Running experiment: " << m << " x " << n << "\n";
        mt19937 rng(12345);
        auto mat = RANDOM_MATRIX(m, n, 0.6, rng); // 60% 0s, 40% 1s

        //init memory for the DP method

        size_t DP_size = sizeof(uint8_t) * m * n; // DP matrix size in bytes
        size_t mat_size = sizeof(uint8_t) * m * n; // input matrix size in bytes
        size_t total_memory = DP_size + mat_size;

        auto start = chrono::high_resolution_clock::now();
        Result result = largest_square(mat);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> time_taken = end - start;

        //memory usage can be estimated in KB

        cout << "Max square size: " << result.maxSize << "\n";
        cout << "Time taken: " << time_taken.count() << " seconds\n";
        cout << "Memory usage: " << total_memory / 1024.0 << " KB\n\n";
    }
}

int main() {
    // Sample matrix 5x5
    vector<vector<uint8_t>> mat = {
        {0,0,0,0,1},
        {0,0,0,0,1},
        {0,0,0,0,0},
        {0,0,0,0,1},
        {0,1,0,1,0}
    };

    Result res = largest_square(mat);
    print_matrix(mat, res);

    // Synthetic experiments
    run_exp();

    return 0;
}
