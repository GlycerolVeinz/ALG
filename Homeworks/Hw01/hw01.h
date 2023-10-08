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

// coordinates structure, made purely for authors convenience, can be easily rewritten without it
struct COORD {
    int x{}, y{}, width{};
    int to_int = y * width + x;
};

// park structure, shouldn't be saved in to map structure for avoiding confusion
struct park {
    COORD top_left_position{};
    bool is_viable = false;
    int forests_count = 0;
};

//Function declarations ================================================================================================

// Function - add_viable_parks - checks mountains in a possible park location, returns park structure
// code should only work with viable parks!!!
park add_viable_parks(map *map, std::vector<park> *viable_parks, int i, int j);

// Function - count_forests_in_park - counts forests in a park, doesn't check viability!
void count_forests_in_park(park *park, map *map, int &max_trees_count);

// Function - read_input - reads input from stdin and saves it to a map structure
map read_input();

// Function - calculate_partial_summs - helps in quick calculation of items in a line
void calculate_partial_summs(map *map, int tile, int &forests_summ, int &mountains_summ);


#endif //HW01_H
