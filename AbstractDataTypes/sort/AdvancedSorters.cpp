//
// Created by safor on 27.1.24.
//

#include "Sorter.h"

namespace MyADTs {
    namespace Sorters {
        namespace Advanced {

//         Quick Sorting ========================================================
            long QuickSorter::partition(vector<int> &vec, long low, long high) {
                int pivot = vec.at(high);
                long i = low - 1;
                for (long j = low; j <= high - 1; ++j) {
                    if ( vec.at(j) <= pivot ) {
                        swapByIndex(vec, ++i, j);
                    }
                }
                swapByIndex(vec, i + 1, high);
                return i + 1;
            }

            void QuickSorter::quickSort(vector<int> &vec, long low, long high) {
                if ( low < high ) {
                    long pi = partition(vec, low, high);
                    quickSort(vec, low, pi - 1);
                    quickSort(vec, pi + 1, high);
                }
            }

            void QuickSorter::sort(vector<int> &vec) {
                quickSort(vec, 0, (long)vec.size() - 1);
            }


//         Merge Sorting ========================================================
            void MergeSorter::sort(vector<int> &vec) {
                mergeSort(vec, 0, (long) vec.size() - 1);
            }

            void MergeSorter::mergeSort(vector<int> &vec, long low, long high) {
                if ( low >= high )
                    return;

                long mid = (low + high) / 2;
                mergeSort(vec, low, mid);
                mergeSort(vec, mid + 1, high);

                splitAndMerge(vec, low, mid, high);
            }

            void MergeSorter::splitAndMerge(vector<int> &vec, long low, long mid, long high) {
                std::pair<vector<int>, vector<int>> pair = split(vec, low, mid, high);
                vector<int> leftVec = pair.first;
                vector<int> rightVec = pair.second;

                merge(vec, leftVec, rightVec, low);
            }

            void MergeSorter::merge(vector<int> &vec, vector<int> leftVec, vector<int> rightVec, long low){
                long i = 0;
                long j = 0;
                long k = low;

                while ( (i < leftVec.size()) && (j < rightVec.size()) ) {
                    if (leftVec.at(i) < rightVec.at(j) ) {
                        vec.at(k) = leftVec.at(i++);
                    } else {
                        vec.at(k) = rightVec.at(j++);
                    }
                    ++k;
                }

                while ( i < leftVec.size() ) {
                    vec.at(k++) = leftVec.at(i++);
                }
            }

            std::pair<vector<int>, vector<int>> MergeSorter::split(vector<int> &vec, long low, long mid, long high){
                vector<int> leftVec(mid - low + 1);
                vector<int> rightVec(high - mid);

                for ( long i = 0; i < leftVec.size(); ++i ) {
                    leftVec.at(i) = vec.at(low + i);
                }

                for ( long j = 0; j < rightVec.size(); ++j ) {
                    rightVec.at(j) = vec.at(mid + 1 + j);
                }

                return std::make_pair(leftVec, rightVec);
            }

//            Heap Sorting ========================================================
            void HeapSorter::sort(vector<int> &vec) {
                long n = (long) vec.size();

//                create heap
                for (long i = (n / 2 - 1); i >= 0; --i) {
                    heapify(vec, n, i);
                }

//                extract elements from heap (sorting)
                for (long i = n - 1; i >= 0; --i) {
                    swapByIndex(vec, 0, i);
                    heapify(vec, i, 0);
                }
            }

            void HeapSorter::heapify(vector<int> &vec, long bottom, long top) {
                long largestId = top;
                long leftChildId = 2 * top + 1;
                long rightChildId = 2 * top + 2;

                if ((leftChildId < bottom) && (vec.at(leftChildId) > vec.at(largestId)) ) {
                    largestId = leftChildId;
                }

                if ((rightChildId < bottom) && (vec.at(rightChildId) > vec.at(largestId)) ) {
                    largestId = rightChildId;
                }

                if (largestId != top ) {
                    swapByIndex(vec, top, largestId);
                    heapify(vec, bottom, largestId);
                }
            }


        } // Advanced
    } // Sorters
} // ADTs
