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

        sim->possibleSimulatorSequences.insert(std::make_pair(sequence, 1));
    }
    return sim;
}


int main() {
    Simulator *sim = readInput();

    std::vector<std::unordered_map<std::string, unsigned long>> possibleSequences;
    possibleSequences.push_back(sim->possibleSimulatorSequences);
    size_t cur = 0;

    while (possibleSequences.size() != (sim->M_sequenceLength - sim->K_simulatorSequenceLength) + 1){
        std::unordered_map<std::string, unsigned long> lastSequence = possibleSequences.at(cur);
        std::unordered_map<std::string, unsigned long> newSequence;

        for (char c : sim->possibleSimulatorStates){
            for (std::pair<std::string, unsigned long> pair : lastSequence){
                std::string newSeq = pair.first + c;
                newSeq = newSeq.substr(1, std::string::npos);

                if (lastSequence.count(newSeq)){
                    newSequence[newSeq] += pair.second;
                }
            }
        }
        possibleSequences.push_back(newSequence);
        ++cur;
    }

    unsigned long res = 0;
    for (std::pair<std::string, unsigned long> pair : possibleSequences.back()){
        res += pair.second;
    }

    std::cout << res << std::endl;
    delete sim;
    return 0;
}
