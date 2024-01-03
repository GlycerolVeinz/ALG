
#include <iostream>
#include <vector>
#include <unordered_set>

typedef struct {
    int  S_simulatorSequencesCount, K_simulatorSequenceLength, M_sequenceLength;
    std::unordered_set<std::string> possibleSimulatorSequences;
    std::unordered_set<char> possibleStates;

    int res;
} Simulator;

Simulator *readInput(){
    auto *sim = new Simulator;
    int S, K, M;
    std::cin >> S >> K >> M;
    sim->S_simulatorSequencesCount = S;
    sim->K_simulatorSequenceLength = K;
    sim->M_sequenceLength = M;

    for (int i = 0; i < S; ++i) {
        std::string sequence;

        for (int j = 0; j < K; ++j) {
            char letter;
            std::cin >> letter;

            sim->possibleStates.insert(letter);
            sequence.push_back(letter);
        }

        sim->possibleSimulatorSequences.insert(sequence);
    }
    return sim;
}


bool validStr(Simulator *sim, std::string &currentString) {
    bool ret = false;
    if (currentString.length() < sim->K_simulatorSequenceLength) {
        ret = true;
    } else {
        std::string lastKChars = currentString.substr(currentString.length() - sim->K_simulatorSequenceLength, sim->K_simulatorSequenceLength);
//        check if there is a possible sequence like that
        for (const std::string& sequence : sim->possibleSimulatorSequences){
            if (sequence == lastKChars){
                ret = true;
                break;
            }
        }
    }

    return ret;
}


void generateAndCheckStrings(Simulator *sim, std::string& currentStr, int len){
    if (len == sim->M_sequenceLength){
//        std::cerr << currentStr << "\n";
        ++sim->res;
        return;
    }

    for (char c : sim->possibleStates){
        currentStr.push_back(c);
        if (validStr(sim, currentStr))
            generateAndCheckStrings(sim, currentStr, len + 1);
        currentStr.pop_back();
    }
}

int main()
{
    Simulator *sim = readInput();

    std::string newStr;
    generateAndCheckStrings(sim, newStr, 0);

    std::cout << sim->res << std::endl;
    delete sim;
    return 0;
}

