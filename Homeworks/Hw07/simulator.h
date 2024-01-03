#ifndef HW07_SIMULATOR_H
#define HW07_SIMULATOR_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>


typedef struct {
    unsigned long  S_simulatorSequencesCount, K_simulatorSequenceLength, M_sequenceLength;

    std::unordered_map<std::string, unsigned long> possibleSimulatorSequences;
    std::unordered_set<char> possibleSimulatorStates;

    int res;
} Simulator;

#endif //HW07_SIMULATOR_H
