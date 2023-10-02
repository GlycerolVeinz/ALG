//
// Created by glycerolveinz on 2.10.23.
//

#ifndef HW01_HW01_H
#define HW01_HW01_H

#include <vector>
#include <iostream>

struct park {
    int N_whole_area{}, K_outer_park_area{}, L_inner_park_area_gap{}, S_minimal_mountain_count{};
    int inner_park_length = K_outer_park_area - 2 * L_inner_park_area_gap;

    #define COORD(x, y) (x + y * N_whole_area)
    #define Field 0
    #define Forest 1
    #define Mountain 2

    std::vector<char> park_map;
    std::vector<char> mountains_map_sum;
    std::vector<char> forests_map_count;
};

park read_input();

#endif //HW01_HW01_H
