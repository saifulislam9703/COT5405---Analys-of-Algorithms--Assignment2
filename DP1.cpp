// DP1.cpp
#include <bits/stdc++.h>
#include "helper.h"
using namespace std;

//English letter frequencies %
vector<double> english_freq_percent = ENGLISH_FREQ_RATE;
const double PENALTY = -10.0;
const int INTERMEDIATE_STEPS = 10;
const string SAMPLE_S = "ABCAABCAA";
const string SAMPLE_T = "ABBCAACCBBBBBB";

inline int idx(char c) { return c - 'A'; } // map 'A'..'Z' to 0..25

struct Result {
    double score;
    int s_start;
    int t_start;
    int length;
    string s_sub;
    string t_sub;
};

// compute pairwise score s(i,j)
double pairScore(
    char a,
    char b, 
    const vector<double>& weights, 
    double penalty) 
    {
        if (a == b) return weights[idx(a)];
        else return penalty;
    }

// Update DP table and best positions
void update_DP(
    vector<vector<double>>& DP,
    double& best_score,
    int& bestI,
    int& bestJ,
    const string& S,
    const string& T,
    const vector<double>& weights,
    double penalty)
    {
        for (int i = 0; i < DP.size(); ++i) {
            for (int j = 0; j < DP[0].size(); ++j) {

                double score = pairScore(S[i], T[j], weights, penalty);

                if (i == 0 || j == 0)  //1st row col 
                    DP[i][j] = score;
                else
                    DP[i][j] = std::max(score, DP[i-1][j-1] + score); //DP update

                if (DP[i][j] > best_score) {
                    // update scores and positions
                    best_score = DP[i][j];
                    bestI = i;
                    bestJ = j;
                }
            }
        }
    }


// DP implementation: returns Result
// S, T: input strings
// weights: letter weights  
// penalty: mismatch score
Result common_substring(
    const string& S, 
    const string& T,
    const vector<double>& weights, 
    double penalty) 
    {
        // size of strings
        int n = (int)S.size();
        int m = (int)T.size();
        if (n == 0 || m == 0) {
            return {0.0, 0, 0, 0, "", ""};
        }

        // DP table: DP[i][j] = initialize all 0.0
        vector<vector<double>> DP(n, vector<double>(m, 0.0));

        double best_score = BESTSCORE_PLACEHOLDER;
        int bestI = -1, bestJ = -1;

        //update DP table
        update_DP(DP, best_score, bestI, bestJ, S, T, weights, penalty);

        if (bestI == -1) 
        {
            return {0.0, 0, 0, 0, "", ""};
        }
        
        int S_i = bestI, T_j = bestJ;
        // traceback to get start positions
        while (S_i > 0 && T_j > 0) {
            double score = pairScore(S[S_i], T[T_j], weights, penalty);
            if (DP[S_i][T_j] == DP[S_i-1][T_j-1] + score) 
            {
                // extend backward
                S_i--; 
                T_j--;
            } 
            else break;
        }

        int length = bestI - S_i + 1;

        string s_sub = S.substr(S_i, length);
        string t_sub = T.substr(T_j, length);

        return {best_score, S_i, T_j, length, s_sub, t_sub};
    }

void Scenario1(
    const string& S, 
    const string& T) 
    {
        vector<double> weights_uniform(26, 1.0);

        cout << "\nScenario 1: uniform weights = 1.0, penalty = " << PENALTY << "\n";
        auto result = common_substring(S, T, weights_uniform, PENALTY);

        cout << "S = " << S << "\nT = " << T << "\n";
        cout << "Best score: " << result.score << "\n";
        cout << "S pos: " << result.s_start << "  T pos: " << result.t_start
            << "  length: " << result.length << "\n";
        cout << "S substring: " << result.s_sub << "\n";
        cout << "T substring: " << result.t_sub << "\n";
    }

void Scenario2(
    const string& S, 
    const string& T) 
    {
        // Scenario 2: penalty proportionate to letter freq
        vector<double> weights_freq(26);
        double sum = 0;
        for (int i = 0; i < 26; ++i) 
        { 
            weights_freq[i] = english_freq_percent[i]; sum += weights_freq[i]; 
        }
        // normalize to 0..1 scale (optional) or keep percentages. We'll keep them as provided.
        double w_min = *min_element(weights_freq.begin(), weights_freq.end());
        double w_max = *max_element(weights_freq.begin(), weights_freq.end());

        cout << "\nScenario 2: \n";
        cout << "Weight range: min=" << w_min << "  max=" << w_max << "\n";

        // Run for 10 diff penalty bw w_min and w_max
        for (int step = 0; step <= INTERMEDIATE_STEPS; ++step) {
            double pen = w_min + (w_max - w_min) * (double)step / (double)INTERMEDIATE_STEPS;
            auto res = common_substring(S, T, weights_freq, -pen);
            cout << "penalty = " << pen << " | best_score = " << res.score
                << " | sPos=" << res.s_start << " tPos=" << res.t_start
                << " len=" << res.length << " substr(S)=" << res.s_sub << "\n";
        }
    }

void SyntheticExperiment() 
    {
        cout << "\nSynthetic experiment: random strings (uniform weights)\n";
        mt19937 rng(12345);

        cout << "Select the lengths of the random strings S and T.\n";
        int lenS, lenT;
        cout << "Enter length of string S: ";
        cin >> lenS;
        cout << "Enter length of string T: ";
        cin >> lenT;
        string S2 = RAND_STRING_GENERATOR(lenS, rng);
        string T2 = RAND_STRING_GENERATOR(lenT, rng);

        cout << "================ SYNTHETIC EXPERIMENT FOR SCENARIO 1 ================\n";
        Scenario1(S2, T2);

        cout << "================ SYNTHETIC EXPERIMENT FOR SCENARIO 2 ================\n";
        Scenario2(S2, T2);

    }

int main(int argc, char** argv) {
    mt19937 rng(random_device{}());

    while(true)
    {
        cout << "================MENU================\n";
        cout << "1. Scenario 1\n";
        cout << "2. Scenario 2\n";
        cout << "3. Synthetic Experiment\n";
        cout << "4. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 4) {
            break; // return
        }

        string S, T;
        char default_choice;
        if (choice == 1 || choice == 2) {
            cout << "Do you want to use the default sample strings? (y/n): ";
            cin >> default_choice;
            cin.ignore();

            if (default_choice == 'y' || default_choice == 'Y') {
                S = SAMPLE_S;
                T = SAMPLE_T;
            } 
            else 
            {
                cout << "Enter string S: ";
                getline(cin, S);
                cout << "Enter string T: ";
                getline(cin, T);
            }
        }

        if (choice == 1) {
            Scenario1(S, T);
        } 
        else if (choice == 2) 
        {
            Scenario2(S, T);
        } 
        else if (choice == 3) {
            SyntheticExperiment();
        } 
        else 
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
