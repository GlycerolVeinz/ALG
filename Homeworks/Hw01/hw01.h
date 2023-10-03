//
// Created by glycerolveinz on 2.10.23.
//

#ifndef HW01_HW01_H
#define HW01_HW01_H

#include <vector>
#include <iostream>

#define SUCCESS 0
#define ERR_INPUT 101

struct map {
    int N_whole_area{}, K_outer_park_area{}, L_inner_park_area_gap{}, S_minimal_mountain_count{};
    int inner_park_length = K_outer_park_area - 2 * L_inner_park_area_gap;
    int inner_park_min = L_inner_park_area_gap;
    int inner_park_max = N_whole_area - L_inner_park_area_gap;


    #define Field 0
    #define Forest 1
    #define Mountain 2

    std::vector<char> park_map;
    std::vector<int> mountains_map_sum;
    std::vector<int> forests_map_count;
};

bool is_inner_park(int x, int y, map *map);
int COORD(int x, int y, int width);
map read_input();
void calculate_partial_summs(map *map, char tile, int forests_summ, int mountains_summ);

#endif //HW01_HW01_H
