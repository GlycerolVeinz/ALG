//
// Created by glycerolveinz on 2.10.23.
//

#include "hw01.h"



int main() {

    park park = read_input();

//    inner park must have at least S number of mountains
//    outer park must have maximal amount of forests

//    iterate through the whole map and find optimal park locations
//      from all parks select ones with the most forests
//      output amount of optimal parks



    exit(SUCCESS);
}


park read_input(){
    int N_whole_area, K_outer_park_area, L_inner_park_area_gap, S_minimal_mountain_count;
    std::cin >> N_whole_area >> K_outer_park_area >> L_inner_park_area_gap >> S_minimal_mountain_count;

    park park = {N_whole_area, K_outer_park_area, L_inner_park_area_gap, S_minimal_mountain_count};

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


void calculate_partial_summs(park *park, char tile, int forests_summ, int mountains_summ) {
    switch (tile) {
        case Field:
            park->forests_map_count.push_back(forests_summ);
            park->mountains_map_sum.push_back(mountains_summ);
            break;
        case Forest:
            park->forests_map_count.push_back(++forests_summ);
            park->mountains_map_sum.push_back(mountains_summ);
            break;
        case Mountain:
            park->forests_map_count.push_back(forests_summ);
            park->mountains_map_sum.push_back(++mountains_summ);
            break;
        default:
            std::cout << "Invalid input" << std::endl;
            exit(ERR_INPUT);
    }
}

