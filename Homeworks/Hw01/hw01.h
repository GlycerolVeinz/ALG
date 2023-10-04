//
// Created by glycerolveinz on 2.10.23.
//

#ifndef HW01_H
#define HW01_H

#include <vector>
#include <iostream>

#define SUCCESS 0
#define ERR_INPUT 101

// whole map structure, that we get from stdin
struct map {
    int N_whole_area{}, K_outer_park_area{}, L_inner_park_area_gap{}, S_minimal_mountain_count{};
    int inner_park_length = K_outer_park_area - 2 * L_inner_park_area_gap;
    int inner_park_min = L_inner_park_area_gap;
    int inner_park_max = N_whole_area - L_inner_park_area_gap;

#define Field 0
#define Forest 1
#define Mountain 2

    std::vector<int> park_map;
    std::vector<int> mountains_map_sum;
    std::vector<int> forests_map_count;
};

struct COORD {
    int x{}, y{};
    int width{};
    int to_int = y * width + x;
};

struct park {
    COORD top_left_position{};
    bool is_optimal = false;
    bool is_viable = false;
    int forests_count = 0;
};

park add_viable_parks(map *map, std::vector<park> *viable_parks, int i, int j);
void count_trees_in_park(park *park, map *map, int &max_trees_count);
map read_input();
void calculate_partial_summs(map *map, int tile, int forests_summ, int mountains_summ);


#endif //HW01_H
