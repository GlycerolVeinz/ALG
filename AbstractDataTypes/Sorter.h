//
// Created by safor on 27.1.24.
//

#ifndef ABSTRACTDATATYPES_SORTER_H
#define ABSTRACTDATATYPES_SORTER_H

#include <vector>
#include <iostream>

using std::vector;

namespace MyADTs {
    namespace Sorters {

        class Sorter {
        public:
            Sorter() = default;
            virtual void sort(vector<int> &vec) = 0;

            static void swapByIndex(vector<int> &vec, long i, long j);
        };

        namespace simple {
            class InsertionSorter : public Sorter {
            public:
                void sort(vector<int> &vec) override;
            };

            class SelectionSorter : public Sorter {
            public:
                void sort(vector<int> &vec) override;
            };

            class BubbleSorter : public Sorter {
            public:
                void sort(vector<int> &vec) override;
            };
        }

        namespace Advanced {
            class QuickSorter : public Sorter {
            public:
                void sort(vector<int> &vec) override;

            private:
                void quickSort(vector<int> &vec, long low, long high);
                long partition(vector<int> &vec, long low, long high);
            };

            class MergeSorter : public Sorter {
            public:
                void sort(vector<int> &vec) override;
            private:
                void mergeSort(vector<int> &vec, long low, long high);
                void splitAndMerge(vector<int> &vec, long low, long mid, long high);

                std::pair<vector<int>, vector<int>> split(vector<int> &vec, long low, long mid, long high);

                void merge(vector<int> &vec, vector<int> left, vector<int> right, long low);
            };

            class HeapSorter : public Sorter {
            public:
                void sort(vector<int> &vec) override;

                void heapify(vector<int> &vec, long bottom, long top);
            };
        } // Advanced
    } // Sorters
} // MyADTs

#endif //ABSTRACTDATATYPES_SORTER_H
