//
// Created by glycerolveinz on 2.10.23.
//

#include "hw01.h"

// main ================================================================================================================
int main() {

//    inner map must have at least S number of mountains
//    outer map must have maximal amount of forests
    map map = read_input();

//  iterate through the whole map and find optimal map locations
//  for every possible inner park location
//  check if it has enough mountains (use partial summs)

    std::vector<park> viable_parks;
    int max_trees_count = 0;

    for (int i = 0; i < map.N_whole_area - map.K_outer_park_area; ++i) {
        for (int j = 0; j < map.N_whole_area - map.K_outer_park_area; ++j) {
//          check mountains for viability of a park
            park park = add_viable_parks(&map, &viable_parks, i, j);

//          count forests in a park
            if (! park.is_viable) {
                continue;
            }

            int forests_count = 0;
            for (int k = 0; k < map.K_outer_park_area; ++k) {

            }
        }
    }


//      output amount of optimal parks

    exit(SUCCESS);
}
// EOF main ===========================================================================================================


//bool is_inner_park(int x, int y, map *map) {
//    bool ret = false;
//    if ((x > map->inner_park_min) && (x < map->inner_park_max) && y > (map->inner_park_min) &&
//        (y < map->inner_park_max)) {
//        ret = true;
//    }
//    return ret;
//}


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

park add_viable_parks(map *map, std::vector<park> *viable_parks, int i, int j){
    bool is_viable = false;
    COORD inner_top_left_corner = {j + map->L_inner_park_area_gap, i + map->L_inner_park_area_gap};
    COORD inner_top_right_corner = {j + map->L_inner_park_area_gap + map->inner_park_length,i + map->L_inner_park_area_gap + map->inner_park_length};
    int mountain_count = 0;

    for (int k = 0; k < map->inner_park_length; ++k) {
        mountain_count += map->mountains_map_sum[inner_top_right_corner.to_int + k] - map->mountains_map_sum[inner_top_left_corner.to_int + k - 1];

        if (mountain_count == map->S_minimal_mountain_count) {
            is_viable = true;
            break;
        }
    }

    COORD top_left_corner = {j, i};
    park park = {top_left_corner, false, is_viable, 0};
    viable_parks->push_back(park);

    return park;
}
