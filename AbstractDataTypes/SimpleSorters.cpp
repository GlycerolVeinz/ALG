//
// Created by safor on 27.1.24.
//

#include "Sorter.h"

namespace MyADTs {
    namespace Sorters {

        template <typename T>
        void Sorter<T>::swapByIndex(vector<T> vec, size_t i, size_t j){
            T temp =vec.at(i);
            vec.at(i) = vec.at(j);
            vec.at(j) = temp;
        }

        namespace simple {
            template<typename T>
            void InsertionSorter<T>::sort(vector<T> &vec) {
                for (long i = 1; i < vec.size(); ++i) {
                    T key = vec.at(i);
                    long j = i - 1;
                    
                    while (j >= 0 && vec.at(j) > key) {
                        vec.at(j + 1) = vec.at(j);
                        j--;
                    }
                    vec.at(j + 1) = key;
                }
            }

            template<typename T>
            void SelectionSorter<T>::sort(vector<T> &vec){
                for (long i = 0; i < vec->size() - 1; ++i){
                    long min = i;
                    for (long j = i + 1; j < vec->size(); ++j) {
                        if ( vec->at(j) < vec->at(min) )
                            min = j;
                    }

                    if ( min != i ){
                        swapByIndex(vec, i, min);
                    }
                }
            }

            template<typename T>
            void BubbleSorter<T>::sort(vector<T> &vec) {
                for (long i = 0; i < vec->size() - 1; ++i) {
                    for (long j = 0; j < vec->size() - i - 1; ++j) {
                        if ( vec->at(j) > vec->at(j + 1) )
                            swapByIndex(vec, j, j + 1);
                    }
                }
            }
        }
    }
}


