#include "recursiveSolver.h"


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

    for (char c : sim->possibleSimulatorStates){
        currentStr.push_back(c);
        if (validStr(sim, currentStr))
            generateAndCheckStrings(sim, currentStr, len + 1);
        currentStr.pop_back();
    }
}