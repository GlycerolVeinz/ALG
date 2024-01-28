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

        template <typename T>
        class Sorter {
        public:
            Sorter() = default;
            virtual void sort(vector<T> &vec) = 0;

            void swapByIndex(vector<T> vec, size_t i, size_t j);
        };

        namespace simple {
            template <typename T>
            class InsertionSorter : public Sorter<T> {
            public:
                void sort(vector<T> &vec) override;
            };

            template <typename T>
            class SelectionSorter : public Sorter<T> {
            public:
                void sort(vector<T> &vec) override;
            };

            template <typename T>
            class BubbleSorter : public Sorter<T> {
            public:
                void sort(vector<T> &vec) override;
            };
        }

        namespace Advanced {
            template <typename T>
            class QuickSorter : public Sorter<T> {
            public:
                void sort(vector<T> &vec) override;

            private:
                void quickSort(vector<T> &vec, long low, long high);
                long partition(vector<T> &vec, long low, long high);
            };

            template <typename T>
            class MergeSorter : public Sorter<T> {
            public:
                void sort(vector<T> &vec) override;
            private:
                void mergeSort(vector<T> &vec, long low, long high);
                void splitAndMerge(vector<T> &vec, long low, long mid, long high);

                std::pair<vector<T>, vector<T>> split(vector<T> &vec, long low, long mid, long high);

                void merge(vector<T> &vec, vector<T> left, vector<T> right, long low);
            };

            template <typename T>
            class HeapSorter : public Sorter<T> {
            public:
                void sort(vector<T> &vec) override;

                void heapify(vector<T> &vec, long n, long i);
            };
        } // Advanced
    } // Sorters
} // MyADTs

#endif //ABSTRACTDATATYPES_SORTER_H
