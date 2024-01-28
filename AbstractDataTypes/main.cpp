#include <iostream>
#include <random>

#include "Sorter.h"

using std::vector;

#define vecLen 10

vector<int> createRandVec(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    vector<int> randIntVec;

    randIntVec.reserve(vecLen);
    for (int i = 0; i < vecLen; ++i) {
        randIntVec.push_back(dis(gen));
    }

    return randIntVec;
}

void printVec(const vector<int>& vec){
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    vector<int> randIntVec = createRandVec();
    printVec(randIntVec);

    for (int k = 0; k < 10; ++k){
        auto *qSorter = new MyADTs::Sorters::Advanced::QuickSorter();
        auto *mSorter = new MyADTs::Sorters::Advanced::MergeSorter();
        auto *hSorter = new MyADTs::Sorters::Advanced::HeapSorter();
        auto *iSorter = new MyADTs::Sorters::simple::InsertionSorter();

        vector<int> vec0 = randIntVec;
        iSorter->sort(vec0);
        std::cout << "Insertion Sort: " << std::endl;
        printVec(vec0);

        vector<int> vec1 = randIntVec;
        qSorter->sort(vec1);
        std::cout << "Quick Sort: " << std::endl;
        printVec(vec1);

        vector<int> vec3 = randIntVec;
        hSorter->sort(vec3);
        std::cout << "Heap Sort: " << std::endl;
        printVec(vec3);

        vector<int> vec2 = randIntVec;
        mSorter->sort(vec2);
        std::cout << "Merge Sort: " << std::endl;
        printVec(vec2);

        for (int i = 0; i < randIntVec.size(); ++i) {
            if (vec0.at(i) != vec1.at(i) ||
                vec0.at(i) != vec2.at(i) ||
                vec0.at(i) != vec3.at(i)) {

                std::cerr << "Error at index " << i <<
                          " Vec1: " << vec1.at(i) <<
                          " Vec2: " << vec2.at(i) <<
                          " Vec3: " << vec3.at(i) << std::endl;
            }
        }

        delete iSorter;
        delete qSorter;
        delete mSorter;
        delete hSorter;
    }
    return 0;
}
