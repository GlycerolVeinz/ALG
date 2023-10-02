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



    return 0;
}


park read_input(){
    int N_whole_area, K_outer_park_area, L_inner_park_area_gap, S_minimal_mountain_count;
    std::cin >> N_whole_area >> K_outer_park_area >> L_inner_park_area_gap >> S_minimal_mountain_count;

    park park = {N_whole_area, K_outer_park_area, L_inner_park_area_gap, S_minimal_mountain_count};

    for (int i = 0; i < N_whole_area * N_whole_area; ++i) {
        char tile;
        std::cin >> tile;
        park.park_map.push_back(tile);

        switch (tile) {
            case Field:
                park.forests_map_count.push_back(0);
                park.mountains_map_sum.push_back(0);
                break;
            case Forest:
                park.forests_map_count.push_back(1);
                park.mountains_map_sum.push_back(0);
                break;
            case Mountain:
                park.forests_map_count.push_back(0);
                park.mountains_map_sum.push_back(1);
                break;
        }


    }

    return park;
}
