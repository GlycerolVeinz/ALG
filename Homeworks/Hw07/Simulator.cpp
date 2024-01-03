#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

using std::string;
using std::cin;
using std::cout;


typedef struct{
    unsigned long S, K, M;
    std::unordered_set<string> possibleSimulatorSequences;
} Simulator;

Simulator* readInput() {
    Simulator* sim = new Simulator;
    cin >> sim->S >> sim->K >> sim->M;

    for (int i = 0; i < sim->S; ++i) {
        string seq;
        cin >> seq;
        sim->possibleSimulatorSequences.insert(seq);
    }

    return sim;
}

#define POSSIBLE_STATES {'A', 'B', 'C', 'D'}

// Helper function to get the last K characters or the whole string if shorter
string getLastK(const string& str, int K) {
    int n = (int) str.length();
    return str.substr(std::max(0, n - K), std::min(n, K));
}

unsigned long countSequences(Simulator* sim) {
    // DP table: dp[length][lastKChars] = number of sequences
    std::unordered_map<string, unsigned long> dp[sim->M + 1];

    // Base case
    dp[0][""] = 1; // 1 way to have a sequence of length 0

    // Building the DP table
    for (int length = 1; length <= sim->M; ++length) {

        for (char c : POSSIBLE_STATES) {

            for (auto& [lastKChars, count] : dp[length - 1]) {

                string newLastK = getLastK(lastKChars + c, (int) sim->K);

                if (length < sim->K || sim->possibleSimulatorSequences.count(newLastK)) {
                    dp[length][newLastK] += count;
                }
            }
        }
    }

    // Summing up all valid sequences of length M
    unsigned long result = 0;
    for (auto& [lastKChars, count] : dp[sim->M]) {
        result += count;
    }

////    print dp
//    for (int length = 0; length <= sim->M; ++length) {
//        cout << "length " << length << std::endl;
//        for (auto& [lastKChars, count] : dp[length]) {
//            cout << lastKChars << " " << count << std::endl;
//        }
//        cout << std::endl;
//    }

    return result;
}

int main() {
    Simulator* sim = readInput();
    cout << countSequences(sim) << std::endl;
    delete sim;
    return 0;
}
