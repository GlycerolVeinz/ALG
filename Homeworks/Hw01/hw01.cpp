//
// Created by glycerolveinz on 2.10.23.
//

#include "hw01.h"


int main() {

//    inner map must have at least S number of mountains
//    outer map must have maximal amount of forests
    map map = read_input();

//  iterate through the whole map and find optimal map locations
//  for every possible inner park location
//  check if it has enough mountains (use partial summs)

    for (int i = 0; i < map.N_whole_area; ++i) {
        for (int j = 0; j < map.N_whole_area; ++j) {
//            check mountains here
            if (is_inner_park(i, j, &map)) {

            }

//            check forests here
        }
    }


//      output amount of optimal parks

    exit(SUCCESS);
}

bool is_inner_park(int x, int y, map *map) {
    bool ret = false;
    if ((x > map->inner_park_min) && (x < map->inner_park_max) && y > (map->inner_park_min) &&
        (y < map->inner_park_max)) {
        ret = true;
    }
    return ret;
}

int COORD(int x, int y, int width) {
    return y * width + x;
}

map read_input() {
    int N_whole_area, K_outer_park_area, L_inner_park_area_gap, S_minimal_mountain_count;
    std::cin >> N_whole_area >> K_outer_park_area >> L_inner_park_area_gap >> S_minimal_mountain_count;

    map park = {N_whole_area, K_outer_park_area, L_inner_park_area_gap, S_minimal_mountain_count};

    int forests_summ = 0;
    int mountains_summ = 0;

    for (int i = 0; i < N_whole_area * N_whole_area; ++i) {
        char tile;
        std::cin >> tile;
        park.park_map.push_back(tile);

        if (i % N_whole_area == 0) {
            forests_summ = 0;
            mountains_summ = 0;
        }

        calculate_partial_summs(&park, tile, forests_summ, mountains_summ);
    }

    return park;
}


void calculate_partial_summs(map *map, char tile, int forests_summ, int mountains_summ) {
    switch (tile) {
        case Field:
            map->forests_map_count.push_back(forests_summ);
            map->mountains_map_sum.push_back(mountains_summ);
            break;
        case Forest:
            map->forests_map_count.push_back(++forests_summ);
            map->mountains_map_sum.push_back(mountains_summ);
            break;
        case Mountain:
            map->forests_map_count.push_back(forests_summ);
            map->mountains_map_sum.push_back(++mountains_summ);
            break;
        default:
            std::cout << "Invalid input" << std::endl;
            exit(ERR_INPUT);
    }
}

