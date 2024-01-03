#include "simulator.h"

Simulator *readInput() {
    auto *sim = new Simulator;
    unsigned long S, K, M;
    std::cin >> S >> K >> M;
    sim->S_simulatorSequencesCount = S;
    sim->K_simulatorSequenceLength = K;
    sim->M_sequenceLength = M;

    for (int i = 0; i < S; ++i) {
        std::string sequence;

        for (int j = 0; j < K; ++j) {
            char letter;
            std::cin >> letter;

            sim->possibleSimulatorStates.insert(letter);
            sequence.push_back(letter);
        }

        sim->possibleSimulatorSequences.insert(sequence);
    }


    return sim;
}


int main() {
    Simulator *sim = readInput();

    std::vector<std::unordered_set<std::string>> possibleSequences;
    possibleSequences.push_back(sim->possibleSimulatorSequences);
    int currentSubstring = 1;

    while (possibleSequences.size() - 1 != sim->M_sequenceLength - sim->K_simulatorSequenceLength) {
        std::unordered_set<std::string> lastResults = possibleSequences.back();
        std::unordered_set<std::string> newResults;

        for (const std::string &lastRes: lastResults) {
            std::string tmpStr = lastRes.substr(currentSubstring, std::string::npos);

            for (char c: sim->possibleSimulatorStates) {
                tmpStr.push_back(c);

                if (sim->possibleSimulatorSequences.find(tmpStr) != sim->possibleSimulatorSequences.end()) {
                    std::string newRes = lastRes;
                    newRes.push_back(c);
                    newResults.insert(newRes);
                }

                tmpStr.pop_back();
            }
        }

        possibleSequences.push_back(newResults);
        ++currentSubstring;
    }

    std::cout << possibleSequences.back().size() << std::endl;
    delete sim;
    return 0;
}
