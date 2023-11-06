//
// Created by glycerolveinz on 5.11.23.
//

#ifndef HW02_STORAGEUTILS_H
#define HW02_STORAGEUTILS_H

#include "Storage.h"
#include <vector>
#include <iostream>

Storage readInput();
std::vector<int> readPackages(int boxesCount);
Storage readRooms(int numberOfRooms, std::vector<int> packages);

std::pair<int, int> findBestPackageDelivery(Storage *storage);

#endif //HW02_STORAGEUTILS_H
