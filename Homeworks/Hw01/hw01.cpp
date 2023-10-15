//
// Created by glycerolveinz on 2.10.23.
//

#include "hw01.h"

// main ================================================================================================================
int main() {
    map map = read_input();

//  iterate through the whole map and find optimal map locations
//  for every possible inner park location
//  check if it has enough mountains (use partial summs)
    std::vector<park> viable_parks;
    int max_trees_count = 0;

    for (int i = 0; i < map.N_whole_area - map.K_outer_park_area + 1; ++i) {
        for (int j = 0; j < map.N_whole_area - map.K_outer_park_area + 1; ++j) {
//          check mountains for viability of a park
            park park = add_viable_parks(&map, &viable_parks, i, j);

//          count forests in a viable park
            if (!park.is_viable) continue;

            count_forests_in_park(&park, &map, max_trees_count);
        }
    }

    std::cout << max_trees_count << std::endl;

    exit(SUCCESS);
}
// EOF main ===========================================================================================================


// function ===========================================================================================================
void calculate_partial_summs(map *map, int tile, int &forests_summ, int &mountains_summ) {
    switch (tile) {
        case Field:
            map->forests_map_count.push_back(forests_summ);
            map->mountains_map_sum.push_back(mountains_summ);
            break;
        case Forest:
            ++forests_summ;
            map->forests_map_count.push_back(forests_summ);
            map->mountains_map_sum.push_back(mountains_summ);
            break;
        case Mountain:
            ++mountains_summ;
            map->forests_map_count.push_back(forests_summ);
            map->mountains_map_sum.push_back(mountains_summ);
            break;
        default:
            std::cout << "Invalid input" << std::endl;
            exit(ERR_INPUT);
    }
}

// function ===========================================================================================================
map read_input() {
    int N_whole_area, K_outer_park_area, L_inner_park_area_gap, S_minimal_mountain_count;
    std::cin >> N_whole_area >> K_outer_park_area >> L_inner_park_area_gap >> S_minimal_mountain_count;

    map map = init_map(N_whole_area, K_outer_park_area, L_inner_park_area_gap, S_minimal_mountain_count);

    int forests_summ = 0;
    int mountains_summ = 0;

    for (int i = 0; i < N_whole_area * N_whole_area; ++i) {
        int tile;
        std::cin >> tile;
        map.park_map.push_back(tile);

        if (((i % N_whole_area) == 0) && (i != 0)){
            forests_summ = 0;
            mountains_summ = 0;
        }

        calculate_partial_summs(&map, tile, forests_summ, mountains_summ);
    }

    return map;
}

// function ===========================================================================================================
park add_viable_parks(map *map, std::vector<park> *viable_parks, int i, int j) {
    bool is_viable = false;
    COORD inner_top_left_corner = init_COORD(j + map->L_inner_park_area_gap, i + map->L_inner_park_area_gap, map->N_whole_area);
    COORD inner_top_right_corner = init_COORD(j + map->L_inner_park_area_gap + map->inner_park_length - 1,
                                    i + map->L_inner_park_area_gap, map->N_whole_area);
    int mountain_count = 0;

    for (int k = 0; k < map->inner_park_length; ++k) {
        int next_row = k * map->N_whole_area;
        int left_park = inner_top_left_corner.to_int + next_row;
        int right_park = inner_top_right_corner.to_int + next_row;

        mountain_count += map->mountains_map_sum[right_park] - map->mountains_map_sum[left_park - 1];

        if (mountain_count >= map->S_minimal_mountain_count) {
            is_viable = true;
            break;
        }
    }

    COORD top_left_corner = init_COORD(j, i, map->N_whole_area);
    park park = init_park(top_left_corner, is_viable, 0);
    viable_parks->push_back(park);

    return park;
}

// function ===========================================================================================================
void count_forests_in_park(park *park, map *map, int &max_trees_count) {
    int forests_count = 0;

    for (int k = 0; k < map->K_outer_park_area; ++k) {
        int next_row = k * map->N_whole_area;
        int left_park = park->top_left_position.to_int + next_row;
        int right_park = park->top_left_position.to_int + map->K_outer_park_area + next_row;

        forests_count += map->forests_map_count[right_park - 1] - map->forests_map_count[left_park - 1];
    }

    if (forests_count > max_trees_count) max_trees_count = forests_count;
    park->forests_count = forests_count;
}

map init_map(int N_whole_area, int K_outer_park_area, int L_inner_park_area_gap, int S_minimal_mountain_count){
    map map;
    map.N_whole_area = N_whole_area;
    map.K_outer_park_area = K_outer_park_area;
    map.L_inner_park_area_gap = L_inner_park_area_gap;
    map.S_minimal_mountain_count = S_minimal_mountain_count;
    map.inner_park_length = K_outer_park_area - 2 * L_inner_park_area_gap;
    return map;
}

COORD init_COORD(int x, int y, int width){
    COORD coord;
    coord.x = x;
    coord.y = y;
    coord.width = width;
    coord.to_int = y * width + x;
    return coord;
}

park init_park(COORD top_left_position, bool is_viable, int forests_count){
    park park;
    park.top_left_position = top_left_position;
    park.is_viable = is_viable;
    park.forests_count = forests_count;
    return park;
}
