//
// Created by safor on 27.1.24.
//

#include "Sorter.h"

namespace MyADTs {
    namespace Sorters {
        namespace Advanced {

//         Quick Sorting ========================================================
            template<typename T>
            long QuickSorter<T>::partition(vector<T> &vec, long low, long high) {
                T pivot = vec.at(high);
                long i = low - 1;
                for (long j = low; j <= high - 1; ++j) {
                    if ( vec.at(j) <= pivot ) {
                        swap(vec, ++i, j);
                    }
                }
                swap(vec, i + 1, high);
                return i + 1;
            }

            template<typename T>
            void QuickSorter<T>::quickSort(vector<T> &vec, long low, long high) {
                if ( low < high ) {
                    long pi = partition(vec, low, high);
                    quickSort(vec, low, pi - 1);
                    quickSort(vec, pi + 1, high);
                }
            }

            template<typename T>
            void QuickSorter<T>::sort(vector<T> &vec) {
                quickSort(vec, 0, vec.size() - 1);
            }


//         Merge Sorting ========================================================
            template<typename T>
            void MergeSorter<T>::sort(vector<T> &vec) {
                mergeSort(vec, 0, vec.size() - 1);
            }

            template<typename T>
            void MergeSorter<T>::mergeSort(vector<T> &vec, long low, long high) {
                if ( low < high ) {
                    long mid = (low + high) / 2;
                    mergeSort(vec, low, mid);
                    mergeSort(vec, mid + 1, high);
                    splitAndMerge(vec, low, mid, high);
                }
            }

            template<typename T>
            void MergeSorter<T>::splitAndMerge(vector<T> &vec, long low, long mid, long high) {
                std::pair<vector<T>, vector<T>> pair = split(vec, low, mid, high);
                vector<T> leftVec = pair.first;
                vector<T> rightVec = pair.second;

                merge(vec, leftVec, rightVec, low);
            }

            template<typename T>
            void MergeSorter<T>::merge(vector<T> &vec, vector<T> leftVec, vector<T> rightVec, long low){
                long i = 0;
                long j = 0;
                long k = low;

                while ( (i < leftVec.size()) && (j < rightVec.size()) ) {
                    if (leftVec.at(i) < rightVec.at(j) ) {
                        vec.at(k) = leftVec.at(i);
                        i++;
                    } else {
                        vec.at(k) = rightVec.at(j);
                        j++;
                    }
                    k++;
                }
            }

            template<typename T>
            std::pair<vector<T>, vector<T>> MergeSorter<T>::split(vector<T> &vec, long low, long mid, long high){
                vector<T> leftVec(mid - low + 1);
                vector<T> rightVec(high - mid);

                for ( long i = 0; i < leftVec.size(); ++i ) {
                    leftVec.at(i) = vec.at(low + i);
                }

                for ( long j = 0; j < rightVec.size(); ++j ) {
                    rightVec.at(j) = vec.at(mid + 1 + j);
                }

                return std::make_pair(leftVec, rightVec);
            }

//            Heap Sorting ========================================================
            template<typename T>
            void HeapSorter<T>::sort(vector<T> &vec) {
                long n = vec.size();

                for (long i = (n / 2 - 1); i >= 0; --i) {
                    heapify(vec, n, i);
                }

                for (long i = n - 1; i >= 0; --i) {
                    swap(vec, 0, i);
                    heapify(vec, i, 0);
                }
            }

            template<typename T>
            void HeapSorter<T>::heapify(vector<T> &vec, long n, long i) {
                long largest = i;
                long l = 2 * i + 1;
                long r = 2 * i + 2;

                if ( (l < n) && (vec.at(l) > vec.at(largest)) ) {
                    largest = l;
                }

                if ( (r < n) && (vec.at(r) > vec.at(largest)) ) {
                    largest = r;
                }

                if ( largest != i ) {
                    swap(vec, i, largest);
                    heapify(vec, n, largest);
                }
            }


        } // Advanced
    } // Sorters
} // ADTs
